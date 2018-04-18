/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:34:34 by mc                #+#    #+#             */
/*   Updated: 2018/04/18 22:13:35 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "malloc.h"
# include <unistd.h>
# include <sys/mman.h>

# define TRUE 1
# define FALSE 0

# define TINY_MAX_SIZE 1
# define SMALL_MAX_SIZE (sizeof(void *) * TINY_MAX_SIZE)

# define PADDING (sizeof(void *))

# define MAX_PAGE_TYPES 3
enum						e_page_size
{
	TINY = 0,
	SMALL = 1,
	LARGE = 2
};

typedef unsigned char		t_byte;
typedef int					t_bool;
typedef struct s_chunk		t_chunk;
typedef struct s_block		t_block;
typedef struct s_mem		t_mem;

struct						s_block
{
	t_block		*next;
	size_t		size;
	t_bool		is_free;
	int			padding;
	t_byte		buf[PADDING];
};

struct						s_chunk
{
	t_chunk		*next;
	t_block		*block;
};

struct						s_mem
{
	size_t		page_size;
	t_chunk		*chunks[MAX_PAGE_TYPES];
};

extern t_mem				g_mem;

#endif
