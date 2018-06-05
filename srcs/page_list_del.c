/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_list_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:47:58 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/25 16:48:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "page_list.h"

void	**relink_list(void **f_prev, void **f_next, void **prev, void **next)
{
	void	**tmp;

	if (*next)
	{
		tmp = get_page_prev(*next);
		*tmp = *f_prev;
		tmp = next;
	}
	if (*prev)
	{
		tmp = get_page_next(*prev);
		*tmp = *f_next;
		tmp = prev;
	}
	return (tmp);
}

int		page_list_delone(void **page, char mode)
{
	void	**curr_page_field_prev;
	void	**curr_page_field_next;
	void	*prev_page;
	void	*next_page;
	void	**tmp;

	if ((mode & IGNORE_ELEMENTS_AM) == 0 &&
		(*(get_page_ellements_am(*page))) != 0)
		return (UNMAPPING_NOT_EMPTY_PAGE);
	curr_page_field_prev = get_page_prev(*page);
	curr_page_field_next = get_page_next(*page);
	prev_page = *curr_page_field_prev;
	next_page = *curr_page_field_next;
	if ((prev_page && page == get_page_next(prev_page)) ||
		(next_page && page == get_page_prev(next_page)))
		mode = mode | PTR_FROM_LIST;
	tmp = relink_list(curr_page_field_prev, curr_page_field_next,
		&prev_page, &next_page);
	dealloc(*page, 1);
	if (((mode & DONT_CLEAR_PTR) == 0 && CLEAN_COND(mode)) &&
		(prev_page || next_page))
		*page = *tmp;
	else if ((mode & DONT_CLEAR_PTR) == 0 && CLEAN_COND(mode))
		*page = 0;
	return (OK);
}
