/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:40 by mc                #+#    #+#             */
/*   Updated: 2018/04/18 22:15:58 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "util/util.h"

void			*realloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

    if (!ptr || (size_t)ptr % sizeof(void *))
        return (NULL);
    block = (t_block *)((t_byte *)ptr - sizeof(t_block) + PADDING);
	new = malloc(size);
	if (new && ptr)
	{
		ft_memcpy(new, ptr, (block->size > size) ? size : block->size);
		free(ptr);
	}
	return (new);
}
