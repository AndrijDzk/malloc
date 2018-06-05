/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_free_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 11:57:04 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/27 11:57:05 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block				**nearby_free_block(t_block **begin, void *addr,
								size_t size, char mode)
{
	errno = 0;
	while (begin && *begin)
	{
		if ((*begin)->data.addr <= addr &&
			addr < ((*begin)->data.addr + (*begin)->data.size))
		{
			if (mode != IN_LIST)
			{
				errno = ZONE_ALREADY_FREE;
				return (0);
			}
		}
		else if (((*begin)->data.addr + (*begin)->data.size) == addr ||
			(*begin)->data.addr == (addr + size))
			return (begin);
		begin = &((*begin)->next);
	}
	return (0);
}

static int			relink_free_list(t_block **begin, t_block **buff)
{
	if (begin == 0 || *begin == 0 || buff == 0)
		return (WTF);
	*buff = *begin;
	*begin = (*begin)->next;
	return (OK);
}

static int			insert_to_new_pos(t_block **begin, t_block *block)
{
	t_block		*tmp;

	if (begin == 0 || block == 0)
		return (WTF);
	while (*begin && (block->data.size > (*begin)->data.size))
		begin = &(*begin)->next;
	tmp = *begin;
	*begin = block;
	block->next = tmp;
	return (OK);
}

static t_block		**join_free_blocks(t_zone *zone, t_block **nearby)
{
	void		*addr;
	size_t		size;
	t_block		**nearby2;

	addr = (*nearby)->data.addr;
	size = (*nearby)->data.size;
	while ((nearby2 = nearby_free_block(&(zone->free), addr, size, IN_LIST)))
	{
		if (*nearby == *nearby2)
			errno = WTF;
		enlarge_free_block(nearby2, addr, size);
		addr = (*nearby2)->data.addr;
		size = (*nearby2)->data.size;
		block_list_delone(&(zone->meta), nearby, 0);
		nearby = block_list_find(&(zone->free), addr);
	}
	return (nearby);
}

int					change_free_list(t_zone *zone, void *addr, size_t size)
{
	t_block		*buff;
	t_block		**nearby;

	buff = 0;
	nearby = nearby_free_block(&(zone->free), addr, size, 0);
	if (nearby == 0 && errno == ZONE_ALREADY_FREE)
	{
		errno = 0;
		return (ZONE_ALREADY_FREE);
	}
	if (nearby)
	{
		if (enlarge_free_block(nearby, addr, size) != OK)
			return (WTF);
		nearby = join_free_blocks(zone, nearby);
		if ((*nearby)->next &&
			((*nearby)->data.size > (*nearby)->next->data.size))
			if (relink_free_list(nearby, &buff) != OK ||
				insert_to_new_pos(nearby, buff) != OK)
				return (WTF);
	}
	else
		push_to_zone_free_list(zone, addr, size);
	return (OK);
}
