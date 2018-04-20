/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:06:54 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 02:04:35 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "debug.h"

static int      unalloc_block(t_chunk *chunk, t_block *block, \
                              enum e_page_size e)
{
    t_chunk *unmap_me;

    if (!chunk)
        return (-1);
    if (chunk == g_mem.chunks[e] && chunk->block == block)
    {
        unmap_me = chunk;
        g_mem.chunks[e] = chunk->next;
    }
    else if (chunk->next && chunk->next->block == block)
    {
        unmap_me = chunk->next;
        chunk->next = chunk->next->next;
    }
    else
        unmap_me = NULL;
    if (unmap_me)
    {
        debug_munmap(unmap_me, \
                        block->size + sizeof(t_chunk) + sizeof(t_block) - PADDING);
        return (munmap(unmap_me,                                        \
                   block->size + sizeof(t_chunk) + sizeof(t_block) - PADDING));
    }
    return (unalloc_block(chunk->next, block, e));
}

static void     defrag_blocks(t_block *block)
{
    if (!block)
        return ;
    if (block->next && block->next->is_free && block->is_free)
    {
        debug_defrag(block->buf, block->next->buf, \
                     block->size, block->next->size);
        block->size += block->next->size + sizeof(t_block) - PADDING;
        block->next = block->next->next;
        defrag_blocks(block);
    }
    else
        defrag_blocks(block->next);
}

static void     defrag(t_chunk *chunk, enum e_page_size e)
{
    if (!chunk)
        return ;
    defrag_blocks(chunk->block);
    if (chunk->block && chunk->block->is_free && !chunk->block->next)
    {
        if (!unalloc_block(g_mem.chunks[e], chunk->block, e))
            return ;
    }
    else
        defrag(chunk->next, e);
}

void			free(void *ptr)
{
	t_block	 *block;

    if (!ptr || (size_t)ptr % sizeof(void *))
        return ;
    block = (t_block *)((t_byte *)ptr - sizeof(t_block) + PADDING);
    if (block->size > SMALL_MAX_SIZE * g_mem.page_size)
        unalloc_block(g_mem.chunks[LARGE], block, LARGE);
    else
    {
        block->is_free = TRUE;
        if (block->size <= TINY_MAX_SIZE * g_mem.page_size)
            defrag(g_mem.chunks[TINY], TINY);
        else
            defrag(g_mem.chunks[SMALL], SMALL);
    }
}
