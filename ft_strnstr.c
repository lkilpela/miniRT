/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:56 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/30 15:04:55 by lkilpela         ###   ########.fr       */
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

size_t ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
		++i;
	return (i);
}

int main()
{
	char haystack[100]= "November is a cold month";
	char needle1[30] = "cold";
	char needle2[30] = "November";
	char needle3[30] = "hel";
	char needle4[30] = "Nov";
	char *result;
	result = ft_strnstr(haystack, needle1, 4);
	printf("The substring is: %s\n", result);
	result = ft_strnstr(haystack, needle2, 25);
	printf("The substring is: %s\n", result);
	result = ft_strnstr(haystack, needle3, 4);
	printf("The substring is: %s\n", result);
	result = ft_strnstr(haystack, needle4, 3);
	printf("The substring is: %s\n", result);
	result = ft_strnstr(haystack, needle4, 2);
	printf("The substring is: %s\n", result);
	return (0);

}
	/*
	The strnstr() function locates the first occurrence of the null-terminated string
	needle in the string haystack, where not more than len characters are searched.  Char-
	acters that appear after a `\0' character are not searched.  Since the strnstr() func-
	tion is a FreeBSD specific API, it should only be used when portability is not a con-
	cern.
	RETURN VALUES
	If needle is an empty string, haystack is returned; if needle occurs nowhere in
	haystack, NULL is returned; otherwise a pointer to the first character of the first
	occurrence of needle is returned.

	*/
