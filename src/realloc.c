/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:40 by mc                #+#    #+#             */
/*   Updated: 2018/04/21 13:02:24 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void			*realloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

    if (!ptr || (size_t)ptr % PADDING)
        return (NULL);
    block = (t_block *)((t_byte *)ptr - META_BLOCK_SIZE); //TODO: search block by addr
	new = malloc(size);
	if (new && ptr)
	{
		ft_memcpy(new, ptr, (block->size > size) ? size : block->size);
		free(ptr);
	}
	return (new);
}
