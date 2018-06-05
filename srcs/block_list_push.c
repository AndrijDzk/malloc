/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_list_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:06:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 11:06:15 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block_list.h"
#include "types.h"

void	*block_list_pb(void **page, t_block **begin, t_block_data *data)
{
	void	*tmp;
	void	**first_page;

	first_page = page;
	tmp = 0;
	while (*page && (tmp = new_block_list_node(*page, data)) == 0)
		page = get_page_next(*page);
	if (tmp == 0)
	{
		tmp = page_list_pb(first_page, BLOCK);
		tmp = new_block_list_node(tmp, data);
	}
	while (*begin)
		begin = &((*begin)->next);
	*begin = tmp;
	return (tmp);
}

int		blist_sort_condition(t_block *blck, t_block_data *data, char mode)
{
	if (blck == 0)
		return (0);
	if ((mode & BY_POS))
	{
		if ((mode & DESCENDING) && (data->addr > blck->data.addr))
			return (0);
		if ((mode & DESCENDING) == 0 && (data->addr < blck->data.addr))
			return (0);
	}
	else if ((mode & BY_POS) == 0)
	{
		if ((mode & DESCENDING) && (data->size > blck->data.size))
			return (0);
		if ((mode & DESCENDING) == 0 && (data->size < blck->data.size))
			return (0);
	}
	return (1);
}

void	*blist_p_srt(void **page, t_block **blck, t_block_data *data, char mode)
{
	void	*tmp;
	void	*tmp2;
	void	**first_page;

	first_page = page;
	tmp = 0;
	while (*page && (tmp = new_block_list_node(*page, data)) == 0)
		page = get_page_next(*page);
	if (tmp == 0)
	{
		tmp = page_list_pb(first_page, BLOCK);
		tmp = new_block_list_node(tmp, data);
	}
	while (blist_sort_condition(*blck, data, mode))
		blck = &((*blck)->next);
	tmp2 = *blck;
	*blck = tmp;
	((t_block*)tmp)->next = tmp2;
	return (tmp);
}

void	*push_to_zone_free_list(t_zone *zone, void *addr, size_t size)
{
	t_block_data	data;

	data.exist = 1;
	data.addr = addr;
	data.size = size;
	data.type = BLOCK;
	return (blist_p_srt(&(zone->meta), &(zone->free), &data, 0));
}
