/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 10:30:38 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/26 10:30:52 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_LIST_H
# define BLOCK_LIST_H
# include "meta_structs.h"
# include "error_codes.h"
# include "page_list.h"
# include "base_functions.h"
# include "mode.h"
# include <stdint.h>
# include <unistd.h>

void	*new_block_list_node(void *page, t_block_data *data);

void	*block_list_pb(void **page, t_block **begin, t_block_data *data);

void	*blist_p_srt(void **page, t_block **blck, t_block_data *dt, char mode);

void	*push_to_zone_free_list(t_zone *zone, void *addr, size_t size);

int		block_list_delone(void **page, t_block **begin, unsigned index);

t_block	**block_list_find(t_block **begin, void *addr);

t_block	**block_list_find_by_size(t_block **begin, size_t size);

int		block_node_truncate_start(t_block *node, size_t size);

void	block_list_print(t_block *begin, char *name);

#endif
