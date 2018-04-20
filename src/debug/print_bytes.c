/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:04:09 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 20:38:19 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void print_byte(t_byte byte, int fd, const char *hexa)
{
    write(fd, hexa + ((byte & ~0xf) >> 4), 1);
    write(fd, hexa + (byte & ~0xf0), 1);
}

static void print_bytes_wrapper(t_byte *bytes, size_t size, \
                                int fd, const char *hexa)
{
    if (!size)
        return ;
    print_byte(*bytes, fd, hexa);
    print_bytes_wrapper(bytes + 1, size - 1, fd, hexa);
}

void print_bytes(t_byte *bytes, size_t size, int fd)
{
    print_bytes_wrapper(bytes, size, fd, HEXA);
}

void print_addr(void *addr, int fd)
{
    size_t   bytes;

    bytes = (size_t)addr;
    if (sizeof(void *) == 8)
        bytes = ((bytes & 0x00000000000000ff) << 56) \
              | ((bytes & 0x000000000000ff00) << 40) \
              | ((bytes & 0x0000000000ff0000) << 24) \
              | ((bytes & 0x00000000ff000000) << 8) \
              | ((bytes & 0x000000ff00000000) >> 8) \
              | ((bytes & 0x0000ff0000000000) >> 24) \
              | ((bytes & 0x00ff000000000000) >> 40) \
              | ((bytes & 0xff00000000000000) >> 56);
    else if (sizeof(void *) == 4)
        bytes = ((bytes & 0x000000ff) << 24) \
              | ((bytes & 0x0000ff00) << 8) \
              | ((bytes & 0x00ff0000) >> 8) \
              | ((bytes & 0xff000000) >> 24);
    else if (sizeof(void *) == 2)
        bytes = ((bytes & 0x00ff) << 8) \
              | ((bytes & 0xff00) >> 8);
    write(fd, "0x", 2);
    print_bytes_wrapper((t_byte *)&bytes, sizeof(void *), fd, HEXA);
}
