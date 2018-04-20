/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_free_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:56:53 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 14:57:07 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

static t_block  *search_blocks(t_block *block, size_t size)
{
    if (!block)
        return (NULL);
    if ((block->flag & FREE_FLAG) && block->size >= size)
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

t_block  *find_free_block(size_t size, enum e_page_type e)
{
    t_block *block;

    if (e == LARGE_TYPE)
        return (NULL);
    if (e == TINY_TYPE)
    {
        block = search_chunks(g_chunks[TINY_TYPE], size);
        if (block)
            return (block);
    }
    return search_chunks(g_chunks[SMALL_TYPE], size);
}
