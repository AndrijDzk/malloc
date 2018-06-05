/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:27:14 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/21 16:28:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_FUNCTIONS_H
# define BASE_FUNCTIONS_H
# include <stddef.h>
# include <stdint.h>
# include "meta_structs.h"

void		*alloc(size_t size, short type);

void		dealloc(void *addr, size_t size);

void		**get_page_prev(void *page);

void		**get_page_next(void *page);

uint32_t	*get_page_ellements_am(void *page);

void		*get_page_data_arr(void *page);

int			copy_block_data(t_block_data *dst, t_block_data *src);

void		ft_bzero(void *addr, size_t size);

void		*ft_memcpy(void *dst, void *src, size_t size);

#endif
