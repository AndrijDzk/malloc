/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:21:59 by adzikovs          #+#    #+#             */
/*   Updated: 2018/01/25 14:22:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_H
# define MODE_H

# define IGNORE_ELEMENTS_AM 1
# define PTR_FROM_LIST 2
# define CLEAR_PTR 4
# define DONT_CLEAR_PTR 8

# define BY_POS 1
# define DESCENDING 2

# define TINY 1
# define SMALL 2
# define LARGE 3

# define IN_LIST 1

# define CLEAN_COND(mode) ((mode & CLEAR_PTR) || (mode & PTR_FROM_LIST) == 0)

#endif
