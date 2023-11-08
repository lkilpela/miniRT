/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:06:16 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/08 14:45:35 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (s == NULL)
		return (NULL);
	
	size_t s_len = ft_strlen(s);

	if (start >= s_len)
		return (ft_strdup(""));
	if(start + len > s_len)
		len = s_len - start;
	
	char *new_str = (char*)malloc(sizeof(char) * (len + 1));

	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s + start, len + 1);
	return (new_str);
}

/**
 * 1. Handle NULL input string: If the input string s is NULL, the function 
 * immediately returns NULL. This prevents any further operations from being 
 * performed on s, which would result in undefined behavior since s doesn't 
 * point to a valid string.
 * 
 * 2. Handle start index greater than string length: If the start index is greater 
 * than or equal to the length of the string, the function returns an empty 
 * string. This is because there are no characters to include in the substring.
	* To return an empty string in the substr function, you can use the strdup 
	* function with an empty string as the argument. The strdup function allocates 
	* memory for a new string and copies the given string into it.
	*
 * 3. Adjust len if it extends beyond the end of the string: If the sum of the 
 * start index and the requested length is greater than the length of the string, 
 * the function adjusts the length of the substring to go up to the end of the string.
 * 
 * 4. Check if memory allocation was successful: If malloc fails to allocate memory 
 * for the new string, it will return NULL. The function checks for this and returns 
 * NULL if allocation failed.
 * 
 * 5.Copy the specified substring to the new string: The function uses strlcpy to 
 * copy the substring from s to new_str. The strlcpy function takes care of 
 * null-terminating the new string.
	* Here, s + start is the source string (the starting point of the substring), new_str 
	* is the destination string, and len + 1 is the size of the destination buffer. 
	* The + 1 is for the null terminator that ends the string.
	* 
	* This line of code copies len characters from the source string to the destination 
	* string, and then null-terminates the destination string. This creates the desired 
	* substring.
 * 
 */