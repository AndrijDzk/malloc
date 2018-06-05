/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:12:55 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/21 15:13:25 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_STRUCTS_H
# define META_STRUCTS_H
# define TINY_ZONE_PAGES 500
# define SMALL_ZONE_PAGES 10000
# include <stddef.h>

typedef struct		s_block_data
{
	char			exist;
	short			type;
	void			*addr;
	size_t			size;
}					t_block_data;

typedef struct		s_block
{
	t_block_data	data;
	struct s_block	*next;
}					t_block;

typedef struct		s_zone
{
	void			*addr;
	void			*meta;
	t_block			*free;
	t_block			*allocated;
}					t_zone;

typedef struct		s_meta
{
	t_zone			tiny;
	t_zone			small;
	t_zone			large;
	void			*reg;
	t_block			*reg_data;
}					t_meta;

#endif
