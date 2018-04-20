/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 22:45:53 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 15:19:51 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdlib.h>
# include <unistd.h>

# define HEXA "0123456789abcdef"

typedef unsigned char		t_byte;

void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *str);
void        	ft_putnbr_fd(int n, int fd);
void        	ft_putstr_fd(char const *s, int fd);

#endif
