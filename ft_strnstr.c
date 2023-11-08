/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:56 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/07 14:06:22 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t n;

	n = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack != 0 && n <= len)
	{
		if (ft_strncmp(haystack, needle, n) == 0)
			return ((char *)haystack);
		++needle;
		--len;
	}
	return (0);
}

/**
 * 1. Define the function strnstr that takes three parameters: haystack, needle,
 * and len.
 * 
 * 2. Calculate the length of needle and store it in n. 
 * 
 * 3. If needle is an empty string (i.e., its first character is the null character),
 * return haystack. This is because an empty string is considered to be found at the
 * start of any string.
 * 
 * 4. Start a loop that continues as long as the current character of haystack is not the 
 * null character and n is less than or equal to len.
 * 
 * 5. Inside the loop, compare the first n characters of haystack with needle using strncmp.
 * If they are equal (i.e., strncmp returns 0), return the current position in haystack.
 * 
 * 6. If the first n characters of haystack are not equal to needle, increment the pointer 
 * to haystack and decrement len.
 * 
 * 7. If the loop finishes without finding needle in haystack within the first len characters
 * return a null pointer to indicate that needle was not found.
 * 
 */