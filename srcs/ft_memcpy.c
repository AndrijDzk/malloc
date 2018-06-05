/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:32:40 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/30 13:32:41 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, void *src, size_t size)
{
	char	*buff1;
	char	*buff2;
	size_t	i;

	buff1 = dst;
	buff2 = src;
	i = 0;
	while (i < size)
	{
		buff1[i] = buff2[i];
		i++;
	}
	return (dst);
}
