/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:40 by mc                #+#    #+#             */
/*   Updated: 2018/04/25 06:40:29 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void			*realloc(void *ptr, size_t size)
{
	void	*new;
	t_block	*block;

    if (!ptr || (size_t)ptr % PADDING)
        return (NULL);
    pthread_mutex_lock(&g_mutex);
    block = find_block_by_addr(ptr);
    pthread_mutex_unlock(&g_mutex);
    if (!block)
        return (NULL);
	new = malloc(size);
	if (new && ptr)
	{
		ft_memcpy(new, ptr, (block->size > size) ? size : block->size);
		free(ptr);
	}
	return (new);
}
