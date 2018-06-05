/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:34:34 by adzikovs          #+#    #+#             */
/*   Updated: 2018/02/02 12:34:36 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "../libft/libft.h"

static t_block	*find_first_from_addr(t_block *block, void *start)
{
	t_block		*ret;
	void		*curr;

	ret = 0;
	while (block)
	{
		curr = block->data.addr;
		if (curr >= start && (ret == 0 || curr <= ret->data.addr))
			ret = block;
		block = block->next;
	}
	return (ret);
}

size_t			show_zone_alloc_mem(t_zone *zone, char *type)
{
	t_block		*tmp;
	void		*addr;
	void		*end;
	size_t		size;
	size_t		ret;

	ret = 0;
	if (type && (type[0] == 'T' || type[0] == 'S'))
		ft_printf("%s : %p\n", type, zone->addr);
	else if (zone->allocated)
		ft_printf("%s : %p\n", type, zone->allocated->data.addr);
	else
		ft_printf("%s : unallocated\n", type);
	tmp = find_first_from_addr(zone->allocated, zone->addr);
	while (tmp)
	{
		addr = tmp->data.addr;
		size = tmp->data.size;
		end = addr + size - 1;
		ret += size;
		ft_printf("%p - %p : %zu bytes\n", addr, end, size);
		addr = addr + size;
		tmp = find_first_from_addr(zone->allocated, addr);
	}
	return (ret);
}

void			show_alloc_mem(void)
{
	size_t		total;

	if (g_meta == 0)
	{
		ft_printf("TINY : uninitiated\n");
		ft_printf("SMALL : uninitiated\n");
		ft_printf("LARGE : uninitiated\n");
		ft_printf("Total : 0 bytes\n");
	}
	else
	{
		total = 0;
		total += show_zone_alloc_mem(&(g_meta->tiny), "TINY");
		total += show_zone_alloc_mem(&(g_meta->small), "SMALL");
		total += show_zone_alloc_mem(&(g_meta->large), "LARGE");
		ft_printf("Total : %zu bytes\n", total);
	}
}
