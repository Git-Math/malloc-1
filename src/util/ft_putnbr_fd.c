/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 17:02:47 by mcanal            #+#    #+#             */
/*   Updated: 2018/04/20 01:06:29 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Print an integer on the specified file descriptor.
*/

#include "util.h"
#include <unistd.h>

static void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void    	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483647 - 1)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd((char)(n + '0'), fd);
}
