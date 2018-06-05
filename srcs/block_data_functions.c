/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_data_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 10:53:55 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 10:53:58 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "meta_structs.h"

int		copy_block_data(t_block_data *dst, t_block_data *src)
{
	dst->type = src->type;
	dst->addr = src->addr;
	dst->size = src->size;
	return (0);
}
