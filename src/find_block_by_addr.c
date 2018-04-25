/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block_by_addr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 05:54:29 by mc                #+#    #+#             */
/*   Updated: 2018/04/25 06:29:54 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"


static t_block  *search_blocks(t_block *block, void *addr)
{
    if (!block)
        return (NULL);
    if (block->buf == addr)
        return (block);
    return (search_blocks(block->next, addr));
}

static t_block  *search_chunks(t_chunk *chunk, void *addr)
{
    t_block  *block;

    if (!chunk)
        return (NULL);
    if ((t_chunk *)addr - chunk > 0)
    {
        block = search_blocks(chunk->block, addr);
        if (block)
            return (block);
    }
    return (search_chunks(chunk->next, addr));
}

t_block         *find_block_by_addr(void *addr)
{
    t_block *ret;

    ret = search_chunks(g_chunks[TINY_TYPE], addr);
    if (ret)
        return (ret);
    ret = search_chunks(g_chunks[SMALL_TYPE], addr);
    if (ret)
        return (ret);
    return (search_chunks(g_chunks[LARGE_TYPE], addr));
}
