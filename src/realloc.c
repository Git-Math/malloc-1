/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:40 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 22:37:18 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void			*realloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

    if (!ptr || (size_t)ptr % sizeof(void *))
        return (NULL);
    block = (t_block *)((t_byte *)ptr - sizeof(t_block) + PADDING); //TODO: search block by addr
	new = malloc(size);
	if (new && ptr)
	{
		ft_memcpy(new, ptr, (block->size > size) ? size : block->size);
		free(ptr);
	}
	return (new);
}
