/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:34:34 by mc                #+#    #+#             */
/*   Updated: 2018/04/21 13:15:12 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "malloc.h"
# include "util/util.h"
# include "debug/debug.h"

# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>

# define TINY_MAX_SIZE 4 //(sizeof(void *))
# define SMALL_MAX_SIZE (sizeof(void *) * TINY_MAX_SIZE)

# define PADDING (sizeof(void *) * 2)
# define META_BLOCK_SIZE (sizeof(t_block) - PADDING)
# define META_CHUNK_SIZE (sizeof(t_chunk) + META_BLOCK_SIZE)

# define MAX_PAGE_TYPES 3
enum						e_page_type
{
	TINY_TYPE = 0,
	SMALL_TYPE = 1,
	LARGE_TYPE = 2
};

enum						e_flag
{
    ERROR_FLAG = (1 << 0),
    TINY_FLAG = (1 << 1),
    SMALL_FLAG = (1 << 2),
    LARGE_FLAG = (1 << 3),
    FREE_FLAG = (1 << 4)
};

typedef struct s_chunk		t_chunk;
typedef struct s_block		t_block;

struct						s_block
{
	t_block		*next;
	size_t		size;
	enum e_flag	flag;
	t_byte		stupid_padding[PADDING - sizeof(enum e_flag)];
	t_byte		buf[PADDING];
};

struct						s_chunk
{
	t_chunk		*next;
	t_block		*block;
};

extern t_chunk				*g_chunks[MAX_PAGE_TYPES];
extern pthread_mutex_t		g_mutex;

t_block			*find_free_block(size_t size, enum e_page_type e);

#endif
