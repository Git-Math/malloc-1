/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:26 by mc                #+#    #+#             */
/*   Updated: 2018/04/17 22:40:14 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_lst           *g_lst = NULL;

static void     *alloc(size_t size, t_flag flag)
{
    t_lst    *l;

    size += sizeof(t_lst) - 1;
    l = (t_lst *)mmap(NULL, size, PROT_READ | PROT_WRITE, \
               MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (l == MAP_FAILED)
        return (NULL);
    l->next = g_lst;
    g_lst = l;
    l->alloc_len = size;
    l->flag = flag;
    return (l->buf);
}

void            *malloc(size_t size)
{
    if (!size)
        return (NULL);
    if (size <= TINY_MAX_SIZE)
        return alloc(size, E_TINY);
    if (size <= SMALL_MAX_SIZE)
        return alloc(size, E_SMALL);
    return alloc(size, E_LARGE);
}
