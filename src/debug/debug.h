/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 01:24:26 by mc                #+#    #+#             */
/*   Updated: 2018/04/27 19:33:30 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "../util/util.h"

# define MMAP_DEBUG_ENV "DEBUG_MMAP"
# define DEFRAG_DEBUG_ENV "DEBUG_DEFRAG"

# define CLR_BLACK "\033[30;01m"
# define CLR_RED "\033[31;01m"
# define CLR_GREEN "\033[32;01m"
# define CLR_YELLOW "\033[33;01m"
# define CLR_BLUE "\033[34;01m"
# define CLR_MAGENTA "\033[35;01m"
# define CLR_CYAN "\033[36;01m"
# define CLR_WHITE "\033[37;01m"
# define CLR_RESET "\033[0m"

void		print_bytes(t_byte *bytes, size_t size, int fd);
void		print_addr(void *addr, int fd);

void		debug_mmap(void *addr, size_t size);
void		debug_munmap(void *addr, size_t size);
void		debug_defrag(void *addr1, void *addr2, size_t size1, size_t size2);
void		debug_split(void *addr1, void *addr2, size_t size1, size_t size2);
void		debug_reuse(void *addr, size_t size1, size_t size2);

void		hex_dump(t_byte *bytes, size_t size, int fd);

char		*get_env(char *key);

#endif
