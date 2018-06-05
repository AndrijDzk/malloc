/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:01:39 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 13:01:42 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "base_functions.h"
#include "types.h"
#include "block_list.h"

int		init_reg(void)
{
	t_block_data	tmp;

	g_meta->reg = mmap(0, getpagesize(), PROT_EXEC | PROT_READ |
			PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	ft_bzero(g_meta->reg, getpagesize());
	g_meta->reg_data = 0;
	tmp.exist = 1;
	tmp.type = REGISTER;
	tmp.addr = g_meta;
	tmp.size = sizeof(t_meta);
	block_list_pb(&(g_meta->reg), &(g_meta->reg_data), &tmp);
	tmp.type = BLOCK;
	tmp.addr = g_meta->reg;
	tmp.size = getpagesize();
	block_list_pb(&(g_meta->reg), &(g_meta->reg_data), &tmp);
	return (0);
}

int		init_zone(t_zone *zone, unsigned pages)
{
	t_block_data	tmp;

	zone->addr = alloc(getpagesize() * pages, DATA_ZONE);
	zone->meta = new_page(BLOCK);
	zone->free = 0;
	zone->allocated = 0;
	if (pages)
	{
		tmp.exist = 1;
		tmp.type = BLOCK;
		tmp.addr = zone->addr;
		tmp.size = getpagesize() * pages;
		blist_p_srt(&(zone->meta), &(zone->free), &tmp, 0);
	}
	return (0);
}

int		init(void)
{
	struct rlimit	rlim;
	size_t			size;

	if ((getrlimit(RLIMIT_AS, &rlim)) == -1)
		return (-1);
	size = getpagesize() * TINY_ZONE_PAGES;
	if (size > rlim.rlim_cur || size > rlim.rlim_max)
		return (-1);
	size = getpagesize() * SMALL_ZONE_PAGES;
	if (size > rlim.rlim_cur || size > rlim.rlim_max)
		return (-1);
	g_meta = mmap(0, sizeof(t_meta), PROT_EXEC | PROT_READ |
			PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	ft_bzero(g_meta, sizeof(*g_meta));
	init_reg();
	init_zone(&(g_meta->tiny), TINY_ZONE_PAGES);
	init_zone(&(g_meta->small), SMALL_ZONE_PAGES);
	init_zone(&(g_meta->large), 0);
	return (0);
}
