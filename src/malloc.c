/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:26 by mc                #+#    #+#             */
/*   Updated: 2018/04/27 19:51:17 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_chunk			*g_chunks[MAX_PAGE_TYPES] = {0};
pthread_mutex_t	g_mutex;

static void		split_block(t_block *block, size_t free_space)
{
	t_block *new;
	size_t	offset;

	if (free_space < sizeof(t_block) + PADDING)
		return ;
	offset = block->size - free_space;
	if (offset % PADDING)
		offset = (offset + PADDING) & ~(PADDING - 1);
	new = (t_block *)((size_t)((t_byte *)block->buf + offset));
	new->size = block->size;
	block->size = (size_t)((t_byte *)new - block->buf);
	new->size = new->size - block->size - META_BLOCK_SIZE;
	new->flag |= FREE_FLAG;
	new->next = block->next;
	block->next = new;
	debug_split(block->buf, new->buf, block->size, new->size);
}

static t_block	*alloc_chunk(t_chunk **chunk_list, size_t buf_size)
{
	t_chunk	*chunk;

	chunk = (t_chunk *)mmap(NULL, buf_size + META_CHUNK_SIZE, \
							PROT_READ | PROT_WRITE, \
							MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	debug_mmap(chunk, buf_size + META_CHUNK_SIZE);
	ft_bzero(chunk, sizeof(t_chunk) + sizeof(t_block));
	chunk->next = *chunk_list;
	*chunk_list = chunk;
	chunk->block = (t_block *)((t_byte *)chunk + sizeof(t_chunk));
	chunk->block->size = buf_size;
	return (chunk->block);
}

static void		*get_buf(size_t size, size_t buf_size, enum e_page_type e)
{
	t_block *block;

	block = find_free_block(size, e);
	if (block)
		debug_reuse(block->buf, block->size, size);
	else
	{
		block = alloc_chunk(&g_chunks[e], buf_size);
		if (!block)
			return (NULL);
		block->flag = 1 << (e + 1);
	}
	block->flag &= ~FREE_FLAG;
	split_block(block, block->size - size);
	return (block->buf);
}

void			*malloc(size_t size)
{
	size_t	tiny_buf_size;
	size_t	small_buf_size;
	void	*ptr;

	if (!size)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	tiny_buf_size = TINY_MAX_SIZE * (size_t)getpagesize() - META_CHUNK_SIZE;
	small_buf_size = SMALL_MAX_SIZE * (size_t)getpagesize() - META_CHUNK_SIZE;
	if (size <= tiny_buf_size)
		ptr = get_buf(size, tiny_buf_size, TINY_TYPE);
	else if (size <= small_buf_size)
		ptr = get_buf(size, small_buf_size, SMALL_TYPE);
	else
		ptr = get_buf(size, size, LARGE_TYPE);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
