/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:19:48 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/07 14:06:22 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	unsigned char *b_char;
	
	i = 0;
	b_char = (unsigned char *)b;
	while (i < len)
	{
		b_char[i] = (unsigned char)c;
		i++;
	}
	return (b);	
}

/**
 * 1. Define the function memset that takes three parameters: a pointer b
 * to the memory area, an integer c to be set, and a size len indicating 
 * the number of bytes to be set to the value.
 * 
 * 2. Pointer Casting: The void* pointer b is cast to an unsigned char* pointer.
 * This is because memset operates at the byte level, and unsigned char 
 * is guaranteed to be 1 byte on every platform.
 * 
 * 3. While Loop: A while loop is used to set each byte in the memory area to the 
 * specified value. The loop continues until i is less than len.
 * 
 * 4. Setting Value: Inside the loop, the ith byte of b is set to c. 
 * The c is cast to an unsigned char to ensure that we're only setting one byte 
 * at a time.
 * 
 * 5. Incrementing Pointer: After setting the value, i is incremented to move to 
 * the next byte.
 * 
 * 6. Once the loop finishes, return the original b.
 * 
 */