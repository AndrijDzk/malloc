/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_truncate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:41:35 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/30 13:41:45 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc_truncate(t_zone *zone, t_block *occupied, size_t size)
{
	t_block		**nearby;
	size_t		new_free_size;
	void		*new_free_addr;

	nearby = block_list_find(&(zone->free),
							occupied->data.addr + occupied->data.size);
	new_free_addr = occupied->data.addr + size;
	new_free_size = occupied->data.size - size;
	occupied->data.size = size;
	if (nearby)
		enlarge_free_block(nearby, new_free_addr, new_free_size);
	else
		push_to_zone_free_list(zone, new_free_addr, new_free_size);
	return (occupied->data.addr);
}
