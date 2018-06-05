/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last_reg_entry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 14:32:59 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/28 14:33:03 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		dealloc_block_list_page(void *page)
{
	void	**field_prev;
	void	**field_next;
	void	*prev;
	void	*next;

	if (page == 0)
		return (WTF);
	field_prev = get_page_prev(page);
	field_next = get_page_next(page);
	prev = *field_prev;
	next = *field_next;
	if (next)
	{
		errno = NOT_LAST_PAGE;
		return (NOT_LAST_PAGE);
	}
	if (prev)
	{
		field_next = get_page_next(prev);
		*field_next = 0;
		dealloc(page, getpagesize());
		return (OK);
	}
	return (WTF);
}

int		check_last_reg_entry(void)
{
	t_block		*carr;
	uint32_t	*elements;

	if (g_meta == 0)
		return (WTF);
	carr = g_meta->reg_data;
	while (carr && carr->next)
		carr = carr->next;
	if (carr->data.type == DEALLOCATED)
	{
		dealloc(carr->data.addr, carr->data.size);
		check_last_reg_entry();
	}
	else if (carr->data.type == BLOCK)
	{
		elements = get_page_ellements_am(carr->data.addr);
		if (*elements == 0)
		{
			if (dealloc_block_list_page(carr->data.addr) == OK)
				check_last_reg_entry();
		}
	}
	return (OK);
}
