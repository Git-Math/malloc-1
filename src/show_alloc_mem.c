/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:12:19 by mc                #+#    #+#             */
/*   Updated: 2018/04/27 19:50:14 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

static size_t		count_blocks(t_block *block, size_t size, int with_hexdump)
{
	if (!block)
		return (size);
	if (!(block->flag & FREE_FLAG))
	{
		print_addr(block->buf, 1);
		ft_putstr_fd(" - ", 1);
		print_addr(block->buf + block->size, 1);
		ft_putstr_fd(" : ", 1);
		ft_putnbr_fd((int)block->size, 1);
		ft_putstr_fd(" octets\n", 1);
		if (with_hexdump)
			hex_dump(block->buf, block->size, 1);
	}
	return (count_blocks(block->next, size + block->size, with_hexdump));
}

static size_t		count_chunks(t_chunk *chunk, size_t size, int with_hexdump)
{
	if (!chunk)
		return (size);
	return (count_chunks(chunk->next, \
						size + count_blocks(chunk->block, 0, with_hexdump), \
						with_hexdump));
}

static size_t		show_chunks(t_chunk *chunk, char *name, int with_hexdump)
{
	ft_putstr_fd(name, 1);
	ft_putstr_fd(" : ", 1);
	print_addr(chunk, 1);
	ft_putstr_fd("\n", 1);
	return (count_chunks(chunk, 0, with_hexdump));
}

void				show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	pthread_mutex_lock(&g_mutex);
	sort_list();
	if (g_chunks[TINY_TYPE])
		total += show_chunks(g_chunks[TINY_TYPE], "TINY", 0);
	if (g_chunks[SMALL_TYPE])
		total += show_chunks(g_chunks[SMALL_TYPE], "SMALL", 0);
	if (g_chunks[LARGE_TYPE])
		total += show_chunks(g_chunks[LARGE_TYPE], "LARGE", 0);
	pthread_mutex_unlock(&g_mutex);
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd((int)total, 1);
	ft_putstr_fd(" octets\n", 1);
}

void				show_alloc_mem_ex(void)
{
	size_t	total;

	total = 0;
	pthread_mutex_lock(&g_mutex);
	sort_list();
	if (g_chunks[TINY_TYPE])
		total += show_chunks(g_chunks[TINY_TYPE], "TINY", 1);
	if (g_chunks[SMALL_TYPE])
		total += show_chunks(g_chunks[SMALL_TYPE], "SMALL", 1);
	if (g_chunks[LARGE_TYPE])
		total += show_chunks(g_chunks[LARGE_TYPE], "LARGE", 1);
	pthread_mutex_unlock(&g_mutex);
	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd((int)total, 1);
	ft_putstr_fd(" octets\n", 1);
}
