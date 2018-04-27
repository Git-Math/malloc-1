/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:40 by mc                #+#    #+#             */
/*   Updated: 2018/04/27 17:34:17 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void			*realloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	if (ptr && !((size_t)ptr % PADDING))
	{
		pthread_mutex_lock(&g_mutex);
		block = find_block_by_addr(ptr);
		pthread_mutex_unlock(&g_mutex);
	}
	else
		block = NULL;
	new = malloc(size);
	if (new && ptr && block)
	{
		ft_memcpy(new, ptr, (block->size > size) ? size : block->size);
		free(ptr);
	}
	return (new);
}
