/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_enlarge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:10:50 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/30 13:10:52 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "base_functions.h"

static int	realloc_simple(t_zone *zone, t_block *occupied,
						t_block **clear, size_t size)
{
	void	*addr_free;
	size_t	new_size;

	occupied->data.size = size;
	addr_free = occupied->data.addr + size;
	new_size = size - occupied->data.size;
	new_size = (*clear)->data.size - new_size;
	block_list_delone(&(zone->meta), clear, 0);
	push_to_zone_free_list(zone, addr_free, new_size);
	return (0);
}

static void	*realloc_complicated(t_block **occupied, size_t size)
{
	void	*ret;

	ret = MALLOC(size);
	ft_memcpy(ret, (*occupied)->data.addr, (*occupied)->data.size);
	FREE((*occupied)->data.addr);
	return (ret);
}

void		*realloc_enlarge(t_zone *zone, char zone_type,
							t_block **occupied, size_t size)
{
	t_block		**nearby;

	nearby = 0;
	if (zone_type == TINY || zone_type == SMALL)
	{
		nearby = block_list_find(&(zone->free),
							(*occupied)->data.addr + (*occupied)->data.size);
		if (nearby && ((*occupied)->data.size + (*nearby)->data.size) >= size)
		{
			realloc_simple(zone, *occupied, nearby, size);
			return ((*occupied)->data.addr);
		}
	}
	return (realloc_complicated(occupied, size));
}
