/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:21:49 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/27 10:11:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t	i;
	
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	return (dst);
}

//The memcpy() function copies n bytes from memory area src to memory area dst.  
//If dst and src overlap, behavior is undefined.
//Applications in which dst and src might overlap should use memmove(3) instead.