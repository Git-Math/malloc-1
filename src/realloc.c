/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:40 by mc                #+#    #+#             */
/*   Updated: 2018/04/28 01:32:27 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void			*realloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

	pthread_mutex_lock(&g_mutex);
	if (ptr && !((size_t)ptr % PADDING))
		block = find_block_by_addr(ptr);
	else
		block = NULL;
	new = nolock_malloc(size);
	if (new && ptr && block)
	{
		ft_memcpy(new, ptr, (block->size > size) ? size : block->size);
		nolock_free(ptr);
	}
	pthread_mutex_unlock(&g_mutex);
	return (new);
}
