/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 00:49:33 by mc                #+#    #+#             */
/*   Updated: 2018/04/27 19:50:35 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void				debug_mmap(void *addr, size_t size)
{
	if (!get_env(MMAP_DEBUG_ENV))
		return ;
	ft_putstr_fd(CLR_GREEN "malloc: " CLR_RESET "mmap'd " CLR_CYAN, 2);
	ft_putnbr_fd((int)size, 2);
	ft_putstr_fd(CLR_RESET " bytes at " CLR_WHITE, 2);
	print_addr(addr, 2);
	ft_putstr_fd(CLR_RESET "\n", 2);
}

void				debug_munmap(void *addr, size_t size)
{
	if (!get_env(MMAP_DEBUG_ENV))
		return ;
	ft_putstr_fd(CLR_RED "free: " CLR_RESET "munmap'd " CLR_CYAN, 2);
	ft_putnbr_fd((int)size, 2);
	ft_putstr_fd(CLR_RESET " bytes at " CLR_WHITE, 2);
	print_addr(addr, 2);
	ft_putstr_fd(CLR_RESET "\n", 2);
}

void				debug_defrag(void *addr1, void *addr2, \
							size_t size1, size_t size2)
{
	if (!get_env(DEFRAG_DEBUG_ENV))
		return ;
	ft_putstr_fd(CLR_YELLOW "free:   " CLR_RESET "joined   " CLR_WHITE, 2);
	print_addr(addr1, 2);
	ft_putstr_fd(CLR_RESET " (" CLR_CYAN, 2);
	ft_putnbr_fd((int)size1, 2);
	ft_putstr_fd(CLR_RESET " bytes) and  " CLR_WHITE, 2);
	print_addr(addr2, 2);
	ft_putstr_fd(CLR_RESET " (" CLR_CYAN, 2);
	ft_putnbr_fd((int)size2, 2);
	ft_putstr_fd(CLR_RESET " bytes)\n", 2);
}

void				debug_split(void *addr1, void *addr2, \
							size_t size1, size_t size2)
{
	if (!get_env(DEFRAG_DEBUG_ENV))
		return ;
	ft_putstr_fd(CLR_BLUE "malloc: " CLR_RESET "splitted " CLR_WHITE, 2);
	print_addr(addr1, 2);
	ft_putstr_fd(CLR_RESET " (" CLR_CYAN, 2);
	ft_putnbr_fd((int)size1, 2);
	ft_putstr_fd(CLR_RESET " bytes) into " CLR_WHITE, 2);
	print_addr(addr2, 2);
	ft_putstr_fd(CLR_RESET " (" CLR_CYAN, 2);
	ft_putnbr_fd((int)size2, 2);
	ft_putstr_fd(CLR_RESET " bytes)\n", 2);
}

void				debug_reuse(void *addr, size_t size1, size_t size2)
{
	if (!get_env(DEFRAG_DEBUG_ENV))
		return ;
	ft_putstr_fd(CLR_MAGENTA "malloc: " CLR_RESET "reused " CLR_WHITE, 2);
	print_addr(addr, 2);
	ft_putstr_fd(CLR_RESET " (" CLR_CYAN, 2);
	ft_putnbr_fd((int)size1, 2);
	ft_putstr_fd(CLR_RESET " bytes) for a " CLR_CYAN, 2);
	ft_putnbr_fd((int)size2, 2);
	ft_putstr_fd(CLR_RESET " bytes buffer\n", 2);
}
