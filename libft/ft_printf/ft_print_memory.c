/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 09:03:41 by adzikovs          #+#    #+#             */
/*   Updated: 2017/02/09 12:01:37 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

int		ft_print_bytes(const void *addr, size_t size, const int *flags)
{
	size_t		i;
	int			icr;
	const char	*buf;
	char		*base;
	int			ret;

	ret = 0;
	buf = addr;
	base = "0123456789abcdef";
	i = 1;
	icr = 1;
	while (i > 0 && i <= 16 && i <= size)
	{
		ret += write(flags[FLAGS_AM], (base + (*(buf + i - 1) & 240) / 16), 1);
		ret += write(flags[FLAGS_AM], (base + (*(buf + i - 1) & 15)), 1);
		if ((i % 2) == 0)
			ret += write(flags[FLAGS_AM], " ", 1);
		i += icr;
	}
	ret += write(flags[FLAGS_AM], "\n", 1);
	return (ret);
}

int		ft_put_memory(va_list par, const int *flags)
{
	size_t	offset;
	size_t	size;
	int		ret;
	void	*addr;

	addr = va_arg(par, void *);
	ret = 0;
	if (!addr)
		return (ret);
	if (flags[3])
		ret += write(flags[FLAGS_AM], "\n", 1);
	size = flags[6];
	offset = 0;
	while (offset < size)
	{
		ret += ft_print_bytes(addr + offset, size - offset, flags);
		offset += 16;
	}
	return (ret);
}

int		ft_put_pointer(va_list par, const int *flags)
{
	uintmax_t	addr;
	int			ret;
	int			sign;
	int			digits;

	addr = va_arg(par, uintmax_t);
	ret = 0;
	sign = 0;
	if (addr)
		sign = 1;
	digits = ft_count_digits(addr, 16);
	ret += ft_field_width(digits, sign, flags, 2);
	ret += ft_prefix(digits, sign, flags, 2);
	ret += ft_put_nbr_base(addr, 16, flags);
	ret += ft_field_width(digits, sign, flags, 4);
	return (ret);
}
