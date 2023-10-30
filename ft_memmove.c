/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:29:34 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/30 15:27:16 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_c;
	char	*src_c;
	size_t	i;

	dst_c = (char *)dst;
	src_c = (char *)src;
	i = 0;
	if (dst_c > src_c)
	{
		while (len > 0)
		{
			--len;
			dst_c[len] = src_c[len];
		}
	}
	else
	{
		while (i < len)
		{
			dst_c[i] = src_c[i];
			++i;
		}
	}
	return (dst);
}

//The memmove() function copies len bytes from string src to string dst.  
//The two strings may overlap;
// the copy is always done in a non-destructive manner.