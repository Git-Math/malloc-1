/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:03:16 by mc                #+#    #+#             */
/*   Updated: 2018/04/17 21:20:05 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY_MAX_SIZE (16 * getpagesize())
# define SMALL_MAX_SIZE (16 * TINY_MAX_SIZE)

enum e_size
{
    E_TINY,
    E_SMALL,
    E_LARGE
};


# include <unistd.h>
# include <stdlib.h>

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem(void);

#endif
