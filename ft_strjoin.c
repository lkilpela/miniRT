/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:38:40 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/18 22:28:57 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Concatenates two strings, allocating memory for the result.
 *
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 *
 * @return The concatenated string, or NULL if the allocation fails.
 */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	return (result);
}

/**
 * 1. The function first checks if either s1 or s2 is NULL. If either is NULL,

	* the function returns NULL immediately. This is to prevent dereferencing a 
    NULL
 * pointer, which would lead to undefined behavior.
 *
 * 2. The function then calculates the lengths of s1 and s2 using strlen.
 *

	* 3. The function allocates memory for a new string that can hold both s1 
    and s2,
 * plus a null terminator. If the memory allocation fails,
	the function returns NULL.
 *

	* 4. The function then copies s1 into the result string using strlcpy. The 
    third argument
 * to strlcpy is the size of the destination buffer, which is len1
	+ 1 to account for
 * the null terminator.
 *
 * 5. The function then concatenates s2 onto the result string using strlcat.
 * The third argument to strlcat is the total size of the result string,
	which is the
 * sum of the lengths of s1 and s2, plus 1 for the null terminator.
 *
 * 6. Finally, the function returns the result string.
 *
 */