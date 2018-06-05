/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 14:54:18 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/10 12:57:54 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

int				ft_scan_prec(const char *str, int j, int *flags)
{
	if (str[j] == '.')
	{
		j++;
		flags[7] = 1;
		if (flags[1])
			flags[11] = 1;
		flags[1] = 0;
		flags[8] = ft_atoi(str + j);
		while (str[j] >= '0' && str[j] <= '9')
			j++;
	}
	return (j);
}

int				ft_scan_len(const char *str, int j)
{
	char	*len[7];
	int		i;

	len[0] = "hh";
	len[1] = "h";
	len[2] = "ll";
	len[3] = "l";
	len[4] = "j";
	len[5] = "z";
	len[6] = 0;
	i = 0;
	while (len[i])
		if (ft_strcmp(str + j, len[i++]))
			return (i);
	return (0);
}
