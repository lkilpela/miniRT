/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:14:15 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/13 14:33:55 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Appends the string pointed to by `src` to the end of the string pointed to
 * by `dst`.It will append at most `dstsize - strlen(dst) - 1` characters.
 * It will then NUL-terminate, unless `dstsize` is 0 or the original `dst`
 * string was longer than `dstsize`.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 *
 * @return The total length of the string that would have been created if
 * `dstsize` were unbounded.
 */
#include "libft.h"

size_t	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	copy;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	copy = min(dstsize - dst_len, src_len + 1);
	if (dst_len < dstsize)
		ft_strlcpy(dst + dst_len, src, copy);
	return (dst_len + src_len);
}

/*
* First, it calculates the lengths of src and dst using the ft_strlen function
* and stores these lengths in src_len and dst_len respectively.Then, it checks
* if dst_len is greater than or equal to dstsize. If it is, the function returns
* the sum of dst_len and src_len. This is because strlcat assumes that dstsize 
is the total size of dst, including the null terminator.
*
* If dst_len is less than dstsize, it calculates the minimum of dstsize
	- dst_len
* and src_len + 1 and stores it in copy. This is the maximum number of 
characters that can be copied from src to dst without overflowing dst.
*
* Then, it calls ft_strlcpy to copy copy characters from src to the end of dst.
*
* Finally, it returns the sum of dst_len and src_len,
	which is the total length that
dst would have if it could hold the entire src.
*/
