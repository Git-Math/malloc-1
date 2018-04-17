/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:06:54 by mc                #+#    #+#             */
/*   Updated: 2018/04/17 22:48:50 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

static t_lst    *find_link(t_lst *l, void *ptr)
{
    if (!l)
        return (NULL);
    if (l->buf == ptr)
        return (l);
    return (find_link(l->next, ptr));
}

void            free(void *ptr)
{
    t_lst    *l;

    l = find_link(g_lst, ptr);
    if (!l)
        return ;
    munmap(l, l->alloc_len);
}
