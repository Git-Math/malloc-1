/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:37:18 by mcanal            #+#    #+#             */
/*   Updated: 2018/04/18 16:15:02 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The  bzero()  function sets the first n bytes of the area starting at s
** to zero (bytes containing '\0').
*/

#include "util.h"

void			ft_bzero(void *s, size_t n)
{
	char *swap;

	if (n)
	{
		swap = s;
		while (n--)
			*swap++ = 0;
	}
}
