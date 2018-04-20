/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:12:19 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 22:01:26 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

static void     show_block(t_block *block)
{
    print_addr(block->buf, 1);
    ft_putstr_fd(" - ", 1);
    print_addr(block->buf + block->size, 1);
    ft_putstr_fd(" : ", 1);
    ft_putnbr_fd(block->size, 1);
    ft_putstr_fd(" octets\n", 1);
};

static size_t   count_blocks(t_block *block, size_t size)
{
    if (!block)
        return (size);
    show_block(block);
    return (count_blocks(block->next, size + block->size));
}

static size_t   count_chunks(t_chunk *chunk, size_t size)
{
    if (!chunk)
        return (size);
    return (count_chunks(chunk->next, size + count_blocks(chunk->block, 0)));
}

static size_t   show_chunks(t_chunk *chunk, char *name)
{
    ft_putstr_fd(name, 1);
    ft_putstr_fd(" : ", 1);
    print_addr(chunk, 1);
    ft_putstr_fd("\n", 1);
    return (count_chunks(chunk, 0));
}

void            show_alloc_mem(void)
{
    size_t  total;

    total = 0;
    if (g_chunks[TINY_TYPE])
        total += show_chunks(g_chunks[TINY_TYPE], "TINY");
    if (g_chunks[SMALL_TYPE])
        total += show_chunks(g_chunks[SMALL_TYPE], "SMALL");
    if (g_chunks[LARGE_TYPE])
        total += show_chunks(g_chunks[LARGE_TYPE], "LARGE");
    ft_putstr_fd("Total : ", 1);
    ft_putnbr_fd(total, 1);
    ft_putstr_fd(" octets\n", 1);
}
