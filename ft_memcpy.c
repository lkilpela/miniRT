/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:21:49 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/07 14:24:42 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_char;
	const unsigned char	*src_char;
	size_t	i;
	
	dst_char = (unsigned char *)dst;
	src_char = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_char[i] = src_char[i];
		i++;
	}
	return (dst);
}

/**
 * Explanation:
 * 1. Function Definition: The function my_memcpy is defined with three parameters:
 * a void* pointer dst to the destination memory area, a const void* pointer src
 * to the source memory area, and a size_t n that indicates the number of bytes 
 * to be copied.
 * 
 * 2. Pointer Casting: The void* pointers dst and src are cast to unsigned char* 
 * pointers * dst_char and src_char respectively. This is because memcpy operates 
 * at the byte level, and unsigned char is guaranteed to be 1 byte on every 
 * platform.
 * 
 * 3. While Loop: A while loop is used to copy each byte from the source memory 
 * area to the destination. The loop continues until i is less than n.
 * 
 * 4. Copying Value: Inside the loop, the ith byte of src_char is copied to the 
 * ith byte of dst_char.
 * 
 * 5.Incrementing Pointer: After copying the value, i is incremented to move to 
 * the next byte.
 * 
 * 6. Return Pointer: Once the loop finishes, the original destination 
 * pointer dst is returned. This is consistent with the behavior of the standard memcpy function.
 * 
 */