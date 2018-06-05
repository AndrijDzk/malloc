/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 10:32:42 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 10:32:50 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block_list.h"
#include <fcntl.h>

void	*new_block_list_node(void *page, t_block_data *data)
{
	t_block		*carr;
	uint32_t	*tmp;

	if (page == 0)
		return (0);
	carr = get_page_data_arr(page);
	while ((void*)(carr + 1) <= (page + getpagesize()))
	{
		if (carr->data.exist == 0)
		{
			copy_block_data(&(carr->data), data);
			carr->data.exist = 1;
			carr->next = 0;
			tmp = get_page_ellements_am(page);
			*tmp = *tmp + 1;
			return (carr);
		}
		carr++;
	}
	return (0);
}

t_block	**block_list_find(t_block **begin, void *addr)
{
	while (begin && *begin)
	{
		if ((*begin)->data.addr == addr)
			return (begin);
		begin = &((*begin)->next);
	}
	return (0);
}

t_block	**block_list_find_by_size(t_block **begin, size_t size)
{
	while (begin && *begin)
	{
		if ((*begin)->data.size >= size)
			return (begin);
		begin = &((*begin)->next);
	}
	return (0);
}
/*
**void	block_list_print(t_block *begin, char *name)
**{
**int		fd;
**
**fd = open(name, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
**while (begin)
**{
**ft_printf("%$%lu - %zu\n", fd, begin->data.addr, begin->data.size);
**begin = begin->next;
**}
**close(fd);
**}
*/
