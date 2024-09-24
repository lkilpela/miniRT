/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:14:15 by lkilpela          #+#    #+#             */
/*   Updated: 2024/07/03 20:02:48 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_min(int a, int b)
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
	copy = ft_min(dstsize - dst_len, src_len + 1);
	if (dst_len < dstsize)
		ft_strlcpy(dst + dst_len, src, copy);
	return (dst_len + src_len);
}
