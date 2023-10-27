/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:52:50 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/27 15:09:33 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Searches for the last occurrence of the character c (an unsigned char) in
 * the string pointed to by s. The terminating null character is considered
 * to be part of the string; therefore if c is `\0', the functions locate
 * the terminating `\0'.
 *
 * @param s The string to search in.
 * @param c The character to search for.
 *
 * @return A pointer to the last occurrence of the character c in the string
 *         s, or NULL if the character is not found.
 */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp;
	
	temp = 0;
	while (*s != 0)
	{
		if (*s == (char) c)
		{
			temp = s;
		}
		++s;
	}
	if (c == 0)
		return ((char *)s);
	return ((char *)temp);
}	