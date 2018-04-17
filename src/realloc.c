/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:40 by mc                #+#    #+#             */
/*   Updated: 2018/04/18 01:00:48 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "util/util.h"

void            *realloc(void *ptr, size_t size)
{
	void	*new;
    size_t  old_size;

    new = malloc(size);
	if (new && ptr)
	{
        old_size = ((t_lst *)((t_byte *)ptr - sizeof(t_lst) + PADDING))->len;
		ft_memcpy(new, ptr, (old_size > size) ? size : old_size);
		free(ptr);
	}
	return (new);
}
