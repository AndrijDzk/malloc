/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:22:20 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 15:22:22 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "types.h"
#include <fcntl.h>

t_meta	*g_meta = 0;

int		free_list_change(t_zone *zone, t_block **tmp, size_t size)
{
	if ((*tmp)->data.size > size)
	{
		if (block_node_truncate_start(*tmp, size) != OK)
			return (WTF);
	}
	else if ((*tmp)->data.size == size)
	{
		if (block_list_delone(&(zone->meta), tmp, 0) != OK)
			return (WTF);
	}
	else
		return (WTF);
	return (OK);
}

void	*malloc_tiny(size_t size)
{
	t_block			**tmp;
	t_block_data	tmp2;
	void			*ret;

	tmp = block_list_find_by_size(&(g_meta->tiny.free), size);
	if (tmp == 0)
	{
		errno = ENOMEM;
		return (0);
	}
	ret = (*tmp)->data.addr;
	if (free_list_change(&(g_meta->tiny), tmp, size) != OK)
		return (0);
	tmp2.exist = 1;
	tmp2.type = BLOCK;
	tmp2.addr = ret;
	tmp2.size = size;
	if (block_list_pb(&(g_meta->tiny.meta), &(g_meta->tiny.allocated), &tmp2)
		== 0)
		return (0);
	return (ret);
}

void	*malloc_small(size_t size)
{
	t_block			**tmp;
	t_block_data	tmp2;
	void			*ret;

	tmp = block_list_find_by_size(&(g_meta->small.free), size);
	if (tmp == 0)
	{
		errno = ENOMEM;
		return (0);
	}
	ret = (*tmp)->data.addr;
	if (free_list_change(&(g_meta->small), tmp, size) != OK)
		return (0);
	tmp2.exist = 1;
	tmp2.type = BLOCK;
	tmp2.addr = ret;
	tmp2.size = size;
	if (block_list_pb(&(g_meta->small.meta), &(g_meta->small.allocated), &tmp2)
		== 0)
		return (0);
	return (ret);
}

void	*malloc_large(size_t size)
{
	t_block_data	tmp2;
	void			*ret;

	ret = alloc(size, DATA);
	if (ret == 0)
	{
		errno = ENOMEM;
		return (0);
	}
	tmp2.exist = 1;
	tmp2.type = BLOCK;
	tmp2.addr = ret;
	tmp2.size = size;
	if (block_list_pb(&(g_meta->large.meta), &(g_meta->large.allocated), &tmp2)
		== 0)
		return (0);
	return (ret);
}

void	*malloc(size_t size)
{
	if (g_meta == 0)
		if ((init()) == -1)
			return (0);
	if (size == 0)
		return (0);
	if (size < 993)
		return (malloc_tiny(size));
	else if (size < 127000)
		return (malloc_small(size));
	else
		return (malloc_large(size));
}
