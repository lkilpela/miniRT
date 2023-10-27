/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:31:47 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/27 15:32:43 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n);

/*
DESCRIPTION
     The memcmp() function compares byte string s1 against byte string s2.  Both strings
     are assumed to be n bytes long.

RETURN VALUES
     The memcmp() function returns zero if the two strings are identical, otherwise returns
     the difference between the first two differing bytes (treated as unsigned char values,
     so that `\200' is greater than `\0', for example).  Zero-length strings are always
     identical.  This behavior is not required by C and portable code should only depend on
     the sign of the returned value.
*/