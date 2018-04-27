/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mc.maxcanal@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:31:08 by mcanal            #+#    #+#             */
/*   Updated: 2018/04/27 19:36:40 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

static void		swap_nodes(t_chunk **head, t_chunk *cur, t_chunk *next)
{
	if (*head == cur)
	{
		*head = next;
		cur->next = next->next;
		next->next = cur;
	}
	else
		swap_nodes(&((*head)->next), cur, next);
}

static void		sort_chunk(t_chunk **head, t_chunk *cur)
{
	t_chunk		*next;

	if (!cur)
		return ;
	next = cur->next;
	if (next && next < cur)
	{
		swap_nodes(head, cur, next);
		sort_chunk(head, *head);
	}
	else
		sort_chunk(head, cur->next);
}

void			sort_list(void)
{
	sort_chunk(&g_chunks[TINY_TYPE], g_chunks[TINY_TYPE]);
	sort_chunk(&g_chunks[SMALL_TYPE], g_chunks[SMALL_TYPE]);
	sort_chunk(&g_chunks[LARGE_TYPE], g_chunks[LARGE_TYPE]);
}
