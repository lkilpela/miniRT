/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:13:11 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/08 15:36:33 by lumik            ###   ########.fr       */
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
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	if (dst == NULL || src == NULL)
		return (0);
		
	src_len = ft_strlen(src);
	i = 0;

	if (dstsize == 0)
		return src_len;
	
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

