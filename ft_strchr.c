/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:51:15 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/16 11:09:35 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_strchr() function locates the first occurrence of 'c' (converted to a
 * char) in the string pointed to by 's'. The terminating null character is
 * considered to be part of the string; therefore if 'c' is '\0', the function
 * locates the terminating '\0'.
 *
 * @param s The string to search.
 * @param c The character to search for.
 *
 * @return A pointer to the located character, or NULL if the character does
 * not appear in the string.
 */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
