/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:26 by mc                #+#    #+#             */
/*   Updated: 2018/04/18 22:17:06 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "util/util.h"

t_mem			g_mem = {0};

static t_block  *search_blocks(t_block *block, size_t size)
{
    if (!block)
        return (NULL);
    if (block->is_free && block->size >= size)
        return (block);
    return (search_blocks(block->next, size));
}

static t_block  *search_chunks(t_chunk *chunk, size_t size)
{
    t_block  *block;

    if (!chunk)
        return (NULL);
    block = search_blocks(chunk->block, size);
    if (block)
        return (block);
    return (search_chunks(chunk->next, size));
}

static t_block  *find_free_block(size_t size, enum e_page_size e)
{
    t_block *block;

    if (e == LARGE)
        return (NULL);
    if (e == TINY)
    {
        block = search_chunks(g_mem.chunks[TINY], size);
        if (block)
            return (block);
    }
    return search_chunks(g_mem.chunks[SMALL], size);
}


static t_block  *alloc_chunk(t_chunk **chunk_list, size_t size)
{
	t_chunk	 *chunk;

    chunk = (t_chunk *)mmap(NULL, \
                            size +  sizeof(t_chunk) + sizeof(t_block) - PADDING, \
                            PROT_READ | PROT_WRITE,                     \
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (chunk == MAP_FAILED)
        return (NULL);
    ft_bzero(chunk, sizeof(t_chunk) + sizeof(t_block));
    chunk->next = *chunk_list;
    *chunk_list = chunk;
    chunk->block = (t_block *)((t_byte *)chunk + sizeof(t_chunk));
    chunk->block->size = size;
	return (chunk->block);
}

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
    new->is_free = TRUE;
    new->next = block->next;
    block->next = new;
}

static void     *get_buf(size_t size, enum e_page_size e)
{
	t_block *block;
	size_t  chunk_size;

    block = find_free_block(size, e);
    if (!block)
    {
        if (e == TINY)
            chunk_size = TINY_MAX_SIZE * g_mem.page_size;
        else if (e == SMALL)
            chunk_size = SMALL_MAX_SIZE * g_mem.page_size;
        else
            chunk_size = size;
        block = alloc_chunk(&g_mem.chunks[e], chunk_size);
        if (!block)
            return (NULL);
    }
    block->is_free = FALSE;
    split_block(block, block->size - size);
    return (block->buf);
}

void			*malloc(size_t size)
{
	if (!size)
		return (NULL);
    if (!g_mem.page_size)
        g_mem.page_size = (size_t)getpagesize();
	if (size <= TINY_MAX_SIZE * g_mem.page_size)
		return (get_buf(size, TINY));
	if (size <= SMALL_MAX_SIZE * g_mem.page_size)
		return (get_buf(size, SMALL));
	return (get_buf(size, LARGE));
}
