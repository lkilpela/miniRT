/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:29:34 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/08 08:47:29 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_char;
	const unsigned char	*src_char;
	
	dst_char = (unsigned char *)dst;
	src_char = (const unsigned char *)src;
	if (dst_char < src_char)
	{
		ft_memcpy(dst, src, len);
	}
	else if (dst_char > src_char)
	{
		while (len > 0)
		{
			dst_char[len] = src_char[len];
			len--;
		}
	}
	return (dst);
}

/**
 * Explanation: 
 * 1. Function Definition: The function my_memmove is defined with three 
 * parameters:
 * a void* pointer dst to the destination memory area, a const void* pointer 
 * src to the source memory area, and a size_t n that indicates the number 
 * of bytes to be moved.
 * 
 * 2. Pointer Casting: The void* pointers dst and src are cast to unsigned 
 * char* pointers dst_char and src_char respectively. This is because memmove 
 * operates at the byte level, and unsigned char is guaranteed to be 1 byte on 
 * every platform.
 * 
 * 3. Direction of Copy: If the destination is before the source in memory, we copy
 * forward from the start of the source to the end. If the destination is after the 
 * source, we copy backward from the end of the source to the start. This ensures 
 * that we don't overwrite any part of the source that we haven't copied yet, which 
 * can happen if the source and destination overlap.

 * 4. While Loop: Inside each branch of the if statement, use a while loop to move 
 each byte from the source to the destination. The loop continues until i is less 
 than n for forward copy, and until n becomes 0 for backward copy.
 * 			while (n-- > 0): This loop will run n times, decrementing n after each 
 *			iteration. The n-- > 0 condition checks if n is greater than 0 before 
			decrementing it. This means the loop will run as long as there are bytes 
			left to copy.

			dst_char[n] = src_char[n];: This line copies the byte at position n from 
			the source to the destination. Because n is decremented after each iteration, 
			this effectively copies the bytes in reverse order, starting from the end.
 * 5. Return Pointer: Once the loop finishes, the original destination pointer dst is 
returned. This is consistent with the behavior of the standard memmove function.
 * 
*/