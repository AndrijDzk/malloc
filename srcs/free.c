/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 11:31:10 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/27 11:31:12 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		free_from_zone(t_zone *zone, void *addr, char mode)
{
	t_block		**alloc;

	alloc = block_list_find(&(zone->allocated), addr);
	if (alloc == 0)
	{
		return (WRONG_ZONE);
	}
	if (mode == TINY || mode == SMALL)
	{
		if (change_free_list(zone, addr, (*alloc)->data.size) != OK)
			return (WTF);
	}
	if (mode == LARGE)
		dealloc(addr, (*alloc)->data.size);
	if (block_list_delone(&(zone->meta), alloc, 0) != OK)
		return (WTF);
	return (OK);
}

void	free(void *addr)
{
	int		ret;

	if (g_meta == 0 || addr == 0)
		return ;
	ret = free_from_zone(&(g_meta->tiny), addr, TINY);
	if (ret == WRONG_ZONE)
		ret = free_from_zone(&(g_meta->small), addr, SMALL);
	if (ret == WRONG_ZONE)
		ret = free_from_zone(&(g_meta->large), addr, LARGE);
	check_last_reg_entry();
}
