/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 00:49:33 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 02:19:05 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void     debug_str(char *s)
{
    write(2, s, ft_strlen(s));
}

void            debug_addr(void *addr)
{
    write(2, "0x", 2);
    ft_putnbr_fd((int)addr, 2); //TODO
}

void            debug_mmap(void *addr, size_t size)
{
    if (!getenv(MMAP_DEBUG_ENV))
        return ;
    debug_str(CLR_GREEN "malloc: " CLR_RESET "mmap'd " CLR_CYAN);
    ft_putnbr_fd(size, 2);
    debug_str(CLR_RESET " bytes at " CLR_WHITE);
    debug_addr(addr);
    debug_str(CLR_RESET "\n");
}

void            debug_munmap(void *addr, size_t size)
{
    if (!getenv(MMAP_DEBUG_ENV))
        return ;
    debug_str(CLR_RED "free: " CLR_RESET "munmap'd " CLR_CYAN);
    ft_putnbr_fd(size, 2);
    debug_str(CLR_RESET " bytes at " CLR_WHITE);
    debug_addr(addr);
    debug_str(CLR_RESET "\n");
}

void            debug_defrag(void *addr1, void *addr2, size_t size1, size_t size2)
{
    if (!getenv(DEFRAG_DEBUG_ENV))
        return ;
    debug_str(CLR_YELLOW "free:   " CLR_RESET "joined   " CLR_WHITE);
    debug_addr(addr1);
    debug_str(CLR_RESET " (" CLR_CYAN);
    ft_putnbr_fd(size1, 2);
    debug_str(CLR_RESET " bytes) and  " CLR_WHITE);
    debug_addr(addr2);
    debug_str(CLR_RESET " (" CLR_CYAN);
    ft_putnbr_fd(size2, 2);
    debug_str(CLR_RESET " bytes)\n");
}

void            debug_split(void *addr1, void *addr2, size_t size1, size_t size2)
{
    if (!getenv(DEFRAG_DEBUG_ENV))
        return ;
    debug_str(CLR_BLUE "malloc: " CLR_RESET "splitted " CLR_WHITE);
    debug_addr(addr1);
    debug_str(CLR_RESET " (" CLR_CYAN);
    ft_putnbr_fd(size1, 2);
    debug_str(CLR_RESET " bytes) into " CLR_WHITE);
    debug_addr(addr2);
    debug_str(CLR_RESET " (" CLR_CYAN);
    ft_putnbr_fd(size2, 2);
    debug_str(CLR_RESET " bytes)\n");
}

void            debug_reuse(void *addr, size_t size1, size_t size2)
{
    if (!getenv(DEFRAG_DEBUG_ENV))
        return ;
    debug_str(CLR_MAGENTA "malloc: " CLR_RESET "reused " CLR_WHITE);
    debug_addr(addr);
    debug_str(CLR_RESET " (" CLR_CYAN);
    ft_putnbr_fd(size1, 2);
    debug_str(CLR_RESET " bytes) for a " CLR_CYAN);
    ft_putnbr_fd(size2, 2);
    debug_str(CLR_RESET " bytes buffer\n");
}
