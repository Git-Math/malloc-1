/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:56:38 by mcanal            #+#    #+#             */
/*   Updated: 2018/04/20 14:59:42 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Print a string on the specified file descriptor.
*/

#include "util.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
