/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:33:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/21 16:33:15 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "page_list.h"
#include <fcntl.h>

void	*new_page(short type)
{
	void	*ret;

	ret = alloc(getpagesize(), type);
	ft_bzero(ret, getpagesize());
	return (ret);
}

void	*page_list_pb(void **begin, short type)
{
	void	*tmp;

	tmp = *begin;
	while (*begin)
	{
		tmp = *begin;
		begin = get_page_next(*begin);
	}
	*begin = new_page(type);
	*(get_page_prev(*begin)) = tmp;
	return (*begin);
}

/*
**void	page_list_print(void *begin)
**{
**	int		fd;
**	char	name[2];
**
**	name[0] = 'a';
**	name[1] = 0;
**	while (begin)
**	{
**		ft_printf("Prev %p, ", *((void**)begin));
**		ft_printf("page - %p, ", begin);
**		ft_printf("next - %p\n", *((void**)(begin + sizeof(void*))));
**		if (name[0] <= 'z')
**		{
**			fd = open(name, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
**			ft_printf("%$%4096m", fd, begin);
**			close(fd);
**			name[0]++;
**		}
**		begin = *get_page_next(begin);
**	}
**}
*/
