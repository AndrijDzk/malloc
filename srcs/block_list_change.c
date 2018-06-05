/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_list_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:46:11 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 15:46:16 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block_list.h"

int		block_node_truncate_start(t_block *node, size_t size)
{
	if (node->data.size < size)
		return (NODE_TOO_SHORT);
	node->data.size = node->data.size - size;
	node->data.addr = (char*)(node->data.addr) + size;
	return (OK);
}
