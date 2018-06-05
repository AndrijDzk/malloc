/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:29:01 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/30 12:29:02 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		**find_allocated_block(void *addr, t_zone **zone, char *zone_type)
{
	t_block		**ret;

	ret = block_list_find(&(g_meta->tiny.allocated), addr);
	if (ret)
	{
		*zone = &(g_meta->tiny);
		*zone_type = TINY;
		return (ret);
	}
	ret = block_list_find(&(g_meta->small.allocated), addr);
	if (ret)
	{
		*zone = &(g_meta->small);
		*zone_type = SMALL;
		return (ret);
	}
	ret = block_list_find(&(g_meta->large.allocated), addr);
	if (ret)
	{
		*zone = &(g_meta->large);
		*zone_type = LARGE;
		return (ret);
	}
	return (ret);
}

void		*realloc(void *addr, size_t size)
{
	t_block		**occupied;
	t_zone		*zone;
	t_block		**nearby;
	char		zone_type;

	if (addr == 0)
		return (0);
	zone = 0;
	zone_type = 0;
	nearby = 0;
	occupied = find_allocated_block(addr, &zone, &zone_type);
	if (occupied == 0)
		return (0);
	if (size == 0)
	{
		FREE(addr);
		return (0);
	}
	if (size > (*occupied)->data.size)
		return (realloc_enlarge(zone, zone_type, occupied, size));
	else if (size == (*occupied)->data.size)
		return (addr);
	else
		return (realloc_truncate(zone, *occupied, size));
}
