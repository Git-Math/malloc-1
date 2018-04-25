/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 13:45:06 by mc                #+#    #+#             */
/*   Updated: 2018/04/25 07:09:35 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void		space_align(size_t size, int fd)
{
	if (!size)
		return ;
	write(fd, " ", 1);
	space_align(size - 1, fd);
}

static void		print_stringified(t_byte *bytes, size_t size, int fd)
{
	if (!size)
		return ;
	if (ft_isprint(*bytes))
		write(fd, bytes, 1);
	else
		write(fd, ".", 1);
	print_stringified(bytes + 1, size - 1, fd);
}

static void		print_spaced_bytes(t_byte *bytes, size_t size, int fd)
{
	if (!size)
	{
		write(fd, " ", 1);
		return ;
	}
	print_bytes(bytes, 1, fd);
	write(fd, " ", 1);
	print_spaced_bytes(bytes + 1, size - 1, fd);
}

static void		dump_last_bytes(t_byte *bytes, size_t size, int fd)
{
	if (size >= sizeof(void *))
	{
		print_spaced_bytes(bytes, sizeof(void *), fd);
		print_spaced_bytes(bytes + sizeof(void *), size - sizeof(void *), fd);
	}
	else
	{
		print_spaced_bytes(bytes, size, fd);
		space_align(1, fd);
	}
	space_align((sizeof(void *) * 2 - size) * 3, fd);
	write(fd, "|", 1);
	print_stringified(bytes, size, fd);
}

void			hex_dump(t_byte *bytes, size_t size, int fd)
{
	print_addr(bytes, fd);
	space_align(2, fd);
	if (size >= sizeof(void *) * 2)
	{
		print_spaced_bytes(bytes, sizeof(void *), fd);
		print_spaced_bytes(bytes + sizeof(void *), sizeof(void *), fd);
		write(fd, "|", 1);
		print_stringified(bytes, sizeof(void *) * 2, fd);
	}
	else
		dump_last_bytes(bytes, size, fd);
	write(fd, "|\n", 2);
	if (size > sizeof(void *) * 2)
		hex_dump(bytes + sizeof(void *) * 2, size - sizeof(void *) * 2, fd);
}
