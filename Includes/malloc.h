/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:19:41 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/20 14:20:16 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include "meta_structs.h"
# include "page_list.h"
# include "block_list.h"
# include "mode.h"
# include "error_codes.h"
# include "types.h"
# include "errno.h"
# define MALLOC(size) malloc(size)
# define REALLOC(addr, size) realloc(addr, size)
# define FREE(addr) free(addr)

extern t_meta	*g_meta;

int			init(void);

int			change_free_list(t_zone *zone, void *addr, size_t size);

int			check_last_reg_entry(void);

void		*malloc(size_t size);

void		*realloc(void *addr, size_t size);

void		*realloc_enlarge(t_zone *zone, char zone_type,
							t_block **occupied, size_t size);

void		show_alloc_mem(void);

void		*realloc_truncate(t_zone *zone, t_block *occupied, size_t size);

void		free(void *addr);

t_block		**find_allocated_block(void *addr, t_zone **zone, char *zone_type);

int			enlarge_free_block(t_block **block, void *addr, size_t size);

#endif
