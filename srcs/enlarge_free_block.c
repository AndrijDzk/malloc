/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enlarge_free_block.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:28:17 by adzikovs          #+#    #+#             */
/*   Updated: 2018/02/02 14:28:18 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int					enlarge_free_block(t_block **block,
	void *addr, size_t size)
{
	if (((*block)->data.addr + (*block)->data.size) == addr)
	{
		(*block)->data.size = (*block)->data.size + size;
		return (OK);
	}
	else if ((*block)->data.addr == (addr + size))
	{
		(*block)->data.addr = (*block)->data.addr - size;
		(*block)->data.size = (*block)->data.size + size;
		return (OK);
	}
	else
		return (WTF);
}
