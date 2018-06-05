/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:13:49 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/23 14:13:52 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

void		**get_page_prev(void *page)
{
	return (page);
}

void		**get_page_next(void *page)
{
	return (page + sizeof(void*));
}

uint32_t	*get_page_ellements_am(void *page)
{
	return (page + 2 * sizeof(void*));
}

void		*get_page_data_arr(void *page)
{
	return (page + 2 * sizeof(void*) + sizeof(uint32_t));
}
