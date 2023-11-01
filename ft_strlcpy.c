/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:13:11 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/01 14:42:30 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Copies up to dstsize - 1 characters from the NUL-terminated string src to
 * dst, NUL-terminating the result.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 *
 * @return The total length of the source string.
 */
#include "libft.h"

size_t	ft_strlcpy(char * restrict dst, const char * restrict src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (dst != NULL || src != NULL)
		return(0);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
/*
The function uses a while loop to copy the string to the destination buffer, 
stopping when either the end of the source string is reached or the maximum size of 
the destination buffer is reached. 
The loop also ensures that the destination buffer is always null-terminated.

Finally, the function returns the length of the source string.
*/