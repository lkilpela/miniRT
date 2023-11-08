/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:12:03 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/07 14:06:22 by lumik            ###   ########.fr       */
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
 * 
 * 1. Define the function strncmp that takes three parameters: two strings s1 and s2,
 * and a number n representing the maximum number of characters to compare.
 * 
 * 2. Start a loop that continues as long as neither s1 nor s2 has reached the end 
 * (*s1 and *s2 are not null) and n is greater than 0.
 * 
 * 3. Inside the loop, compare the current characters of s1 and s2. If they are not 
 * equal, return the difference between the ASCII values of the characters in s1 and s2.
 * 
 * 4. If the current characters of s1 and s2 are equal, decrement n and move to the 
 * next characters in s1 and s2.
 * 
 * 5.If the loop finishes without finding any unequal characters within the first n 
 * characters, return 0 to indicate that the first n characters of s1 and s2 are equal.
 */


