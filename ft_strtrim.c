/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:34:37 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/13 13:21:36 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 != 0 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len != 0 && ft_strchr(set, s1[len - 1]))
		len--;
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len + 1);
	return (result);
}
/**
 * 1. The function first checks if either s1 or set is NULL. If either is NULL,
	the
 * function returns NULL immediately. This is to prevent dereferencing a NULL
 * pointer, which would lead to undefined behavior.
 *

	* 2.The function then uses a while loop and ft_strchr to find the first 
    character in
 * s1 that is not in set. This is the start of the trimmed string.

	* The purpose of finding the first character in s1 that is not in set is 
    to determine

	* where the trimmed string should start. The ft_strtrim function is designed 
    to remove
 * leading and trailing characters that are specified in set from the string s1.
 * To do this, it needs to find the first character in s1 that is not in set
	- this

	* character represents the start of the substring that doesn't include the 
    leading
 * characters to be trimmed.
 * For example, if s1 is " Hello, World! " and set is " ",
	the first character in s1 that
 * is not in set is H, which is the start of the substring "Hello,
	World!" that doesn't
 * include the leading spaces.

	* *s1 checks if the current character in s1 is not the null terminator 
    (which marks the end
 * of the string). If it is the null terminator,
	the condition evaluates to false and the loop
 * ends.ft_strchr(set,
	*s1) checks if the current character in s1 is present in set.
 *

	* ft_strchr is a function that searches for a character in a string and 
    returns a pointer to the first
 * occurrence of the character,
	or NULL if the character is not found. In the context of a condition,
 * NULL is treated as false and any non-null pointer is treated as true.
 *
 * If both conditions are true,
	the loop body is executed. s1++ increments the pointer s1 to point to
 * the next character in the string.
 *

	* 3. The function then finds the index of the last character in s1 that is 
    not in set.

	* This is done by starting from the end of s1 and moving backwards until a 
    character
 * is found that is not in set. This is the end of the trimmed string.
 *
 * len checks if the current length of the string is not zero. If it is zero,
	the condition
 * evaluates to false and the loop ends.
 *
 * ft_strchr(set, s1[len
	- 1]) checks if the current character at the end of s1 is present in set.

	* ft_strchr is a function that searches for a character in a string and 
    returns a pointer to the first
 * occurrence of the character,
	or NULL if the character is not found. In the context of a condition, NULL
 * is treated as false and any non-null pointer is treated as true.
 *
 * If both conditions are true,
	the loop body is executed. len-- decrements the length of the string.
 *

	* 4. The function then allocates memory for a new string that can hold the 
    trimmed string,
 * plus a null terminator. If the memory allocation fails,
	the function returns NULL.
 *

	* 5. The function then copies the trimmed string into the result string 
    using ft_strlcpy.
 *
 * 6. Finally, the function returns the result string.
 *
 */