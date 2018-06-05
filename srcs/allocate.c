/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:27:33 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/21 14:28:34 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "meta_structs.h"
#include "types.h"
#include "error_codes.h"
#include "block_list.h"
#include "malloc.h"

void	*alloc(size_t size, short type)
{
	void			*ret;
	t_block_data	tmp;

	if (size == 0)
		return (0);
	ret = mmap(0, size, PROT_EXEC | PROT_READ |
			PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	tmp.exist = 1;
	tmp.type = type;
	tmp.addr = ret;
	tmp.size = size;
	block_list_pb(&(g_meta->reg), &(g_meta->reg_data), &tmp);
	return (ret);
}

void	dealloc(void *addr, size_t size)
{
	t_block		**tmp;

	if (addr == 0)
		return ;
	tmp = block_list_find(&(g_meta->reg_data), addr);
	if (tmp == 0)
		return ;
	if ((*tmp)->next == 0)
	{
		munmap(addr, size);
		if (block_list_delone(&(g_meta->reg), tmp, 0) != OK)
			return ;
	}
	else
		(*tmp)->data.type = DEALLOCATED;
}
