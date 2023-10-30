/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:12:03 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/30 14:06:06 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != 0 || *s2 !=0) && n > 0)
	{
		if (*s1 != *s2)
			return ((int)*s1 - (int)*s2);
		--n;
		++s1;
		++s2;
	}
	return 0;
}

/**
 * Compares the first n bytes of two strings s1 and s2.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of bytes to compare.
 *
 * @return An integer greater than, equal to, or less than 0, according to
 * whether the string s1 is greater than, equal to, or less than the string s2.
 */