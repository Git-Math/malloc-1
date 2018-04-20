/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:26 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 14:56:30 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "debug.h"

t_chunk				*g_chunks[MAX_PAGE_TYPES] = {0};

static void     split_block(t_block *block, size_t free_space)
{
	t_block *new;

    if (free_space < sizeof(t_block) + 0x20)
        return ;
    new = (t_block *)((size_t)((t_byte *)block->buf \
                               + block->size - free_space + 0x10) & ~0xf);
    new->size = block->size;
    block->size = (size_t)((t_byte *)new - block->buf);
    new->size = new->size - block->size;
    new->flag |= FREE_FLAG;
    new->next = block->next;
    block->next = new;
    debug_split(block->buf, new->buf, block->size, new->size);
}

static t_block  *alloc_chunk(t_chunk **chunk_list, size_t size)
{
	t_chunk	 *chunk;

    chunk = (t_chunk *)mmap(NULL, \
                            size + sizeof(t_chunk) + sizeof(t_block) - PADDING, \
                            PROT_READ | PROT_WRITE,                     \
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); //TODO: round to pagesize
    if (chunk == MAP_FAILED)
        return (NULL);
    debug_mmap(chunk, size + sizeof(t_chunk) + sizeof(t_block));
    ft_bzero(chunk, sizeof(t_chunk) + sizeof(t_block));
    chunk->next = *chunk_list;
    *chunk_list = chunk;
    chunk->block = (t_block *)((t_byte *)chunk + sizeof(t_chunk));
    chunk->block->size = size;
	return (chunk->block);
}

static void     *get_buf(size_t size, size_t chunk_size, enum e_page_type e)
{
	t_block *block;

    block = find_free_block(size, e);
    if (block)
        debug_reuse(block->buf, block->size, size);
    else
    {
        block = alloc_chunk(&g_chunks[e], chunk_size);
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
    size_t  page_size;

	if (!size)
		return (NULL);
    page_size = (size_t)getpagesize();
	if (size <= TINY_MAX_SIZE * page_size)
		return (get_buf(size, TINY_MAX_SIZE * page_size, TINY_TYPE));
	if (size <= SMALL_MAX_SIZE * page_size)
		return (get_buf(size, SMALL_MAX_SIZE * page_size, SMALL_TYPE));
	return (get_buf(size, size, LARGE_TYPE));
}
