/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:37:02 by mc                #+#    #+#             */
/*   Updated: 2018/04/20 21:39:23 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void    *calloc(size_t nmemb, size_t size)
{
    void    *ptr;

    if (!nmemb || !size)
        return (NULL);
    ptr = malloc(nmemb * size);
    if (ptr)
        ft_bzero(ptr, nmemb * size);
    return (ptr);
}
