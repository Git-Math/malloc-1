/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:06:54 by mc                #+#    #+#             */
/*   Updated: 2018/04/28 01:37:17 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

static int		unalloc_block(t_chunk *chunk, t_block *block, \
								enum e_page_type e)
{
	t_chunk *munmap_me;

	if (!chunk)
		return (-1);
	if (chunk == g_chunks[e] && chunk->block == block)
	{
		munmap_me = chunk;
		g_chunks[e] = chunk->next;
		debug_munmap(munmap_me, block->size + META_CHUNK_SIZE);
		return (munmap(munmap_me, block->size + META_CHUNK_SIZE));
	}
	if (chunk->next && chunk->next->block == block)
	{
		munmap_me = chunk->next;
		chunk->next = chunk->next->next;
		debug_munmap(munmap_me, block->size + META_CHUNK_SIZE);
		return (munmap(munmap_me, block->size + META_CHUNK_SIZE));
	}
	return (unalloc_block(chunk->next, block, e));
}

static void		defrag_blocks(t_block *block)
{
	if (!block)
		return ;
	if (block->next \
		&& (block->next->flag & FREE_FLAG) && (block->flag & FREE_FLAG))
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

static void		defrag(t_chunk *chunk, enum e_page_type e)
{
	if (!chunk)
		return ;
	defrag_blocks(chunk->block);
	if (chunk->block && (chunk->block->flag & FREE_FLAG) && !chunk->block->next)
	{
		if (!unalloc_block(g_chunks[e], chunk->block, e))
			return ;
	}
	else
		defrag(chunk->next, e);
}

void			nolock_free(void *ptr)
{
	t_block	*block;

	if (!ptr || (size_t)ptr % PADDING)
		return ;
	block = find_block_by_addr(ptr);
	if (!block)
		return ;
	if (block->flag & LARGE_FLAG)
		unalloc_block(g_chunks[LARGE_TYPE], block, LARGE_TYPE);
	else
	{
		block->flag |= FREE_FLAG;
		if (block->flag & SMALL_FLAG)
			defrag(g_chunks[SMALL_TYPE], SMALL_TYPE);
		else
			defrag(g_chunks[TINY_TYPE], TINY_TYPE);
	}
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	nolock_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
