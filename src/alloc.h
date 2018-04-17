/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:34:34 by mc                #+#    #+#             */
/*   Updated: 2018/04/18 00:02:20 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "malloc.h"
# include <unistd.h>
# include <sys/mman.h>

# define TINY_MAX_SIZE (16 * (size_t)getpagesize())
# define SMALL_MAX_SIZE (16 * TINY_MAX_SIZE)

enum e_flag
{
    E_ERR = (1 << 0),
    E_TINY = (1 << 1),
    E_SMALL = (1 << 2),
    E_LARGE = (1 << 3),
    E_FREE = (1 << 4)
};

typedef enum e_flag         t_flag;
typedef unsigned char       t_byte;
typedef struct s_lst		t_lst;

struct						s_lst
{
	t_lst		*next;
    size_t      alloc_len;
    t_flag      flag;
	t_byte		buf[1];
};

extern t_lst           *g_lst;

#endif
