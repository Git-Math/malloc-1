/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocarray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:41:38 by mc                #+#    #+#             */
/*   Updated: 2018/04/25 07:06:25 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void		*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	size_t	new_size;

	if (!ptr || !nmemb || !size)
		return (NULL);
	new_size = nmemb * size;
	if (new_size / nmemb != size)
		return (NULL);
	return (realloc(ptr, new_size));
}
