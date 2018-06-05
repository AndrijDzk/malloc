/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_list_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 10:32:58 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 10:33:05 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block_list.h"

int		delete_curr(t_block **begin, uint32_t *elements)
{
	t_block	*tmp;

	tmp = (*begin)->next;
	(*begin)->data.exist = 0;
	(*begin)->next = 0;
	*begin = tmp;
	*elements = *elements - 1;
	return (OK);
}

int		delete_next(t_block **begin, uint32_t *elements)
{
	t_block	*tmp;

	tmp = (*begin)->next;
	(*begin)->next = tmp->next;
	tmp->data.exist = 0;
	tmp->next = 0;
	*elements = *elements - 1;
	return (OK);
}

int		block_list_delone(void **page, t_block **begin, unsigned index)
{
	uint32_t	*elements;

	while (begin && *begin && index > 1)
	{
		begin = &((*begin)->next);
		index--;
	}
	if (begin == 0 || *begin == 0 || ((*begin)->next == 0 && index > 0))
		return (INDEX_EXCEEDS_LIST);
	while (((void*)(*begin) < *page ||
		(void*)(*begin) >= (*page + getpagesize())) && *page)
		page = get_page_next(*page);
	if (*page == 0)
		return (NODE_OUT_OF_PAGE);
	elements = get_page_ellements_am(*page);
	if (*elements == 0)
		return (DELETING_FROM_EMPY_PAGE);
	if (index == 0)
		return (delete_curr(begin, elements));
	if (index == 1)
		return (delete_next(begin, elements));
	return (WTF);
}
