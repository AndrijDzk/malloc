/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:24:26 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/21 16:25:05 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_LIST_H
# define PAGE_LIST_H
# include "base_functions.h"
# include "page_list.h"
# include "mode.h"
# include "error_codes.h"
# include <unistd.h>

void	*new_page(short type);

void	*page_list_pb(void **begin, short type);

void	page_list_print(void *begin);

int		page_list_delone(void **page, char mode);

#endif
