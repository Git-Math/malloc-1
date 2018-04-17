/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:40:10 by mcanal            #+#    #+#             */
/*   Updated: 2018/04/17 22:45:38 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The  memcpy()  function  copies  n bytes from memory area src to memory
** area dest.  The memory areas must not overlap.  Use memmove(3)  if  the
** memory areas do overlap.
*/

#include "util.h"

void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dswap;
	const char	*sswap;

	dswap = dest;
	sswap = src;
	if (dest != src)
		while (n--)
			*dswap++ = *sswap++;
	return (dest);
}
