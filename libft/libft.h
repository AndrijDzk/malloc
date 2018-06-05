/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:23:45 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/21 14:23:57 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdarg.h>
# include <inttypes.h>
# include "../Includes/malloc.h"

int		ft_printf(const char *str, ...);

int		ft_atoi(const char *str);

void	ft_bzero(void *addr, size_t size);

int		ft_strcmp(const char *s1, const char *s2);

int		ft_strdiff(const char *s1, const char *s2);

int		ft_find_char(char *str, char c);

int		ft_strlen(const char *str);

char	*ft_strcpy(char *dst, const char *src);

char	*ft_strdup(const char *s1);

char	*ft_strsub(const char *s, unsigned int start, size_t len);

char	*ft_strjoin(const char *s1, const char *s2);

int		ft_count_digits(uintmax_t value, int base);

long	ft_power(long value, long power);

#endif
