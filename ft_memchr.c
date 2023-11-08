/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:30:19 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/08 10:00:06 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;
	
	ptr = (unsigned char *)s;
	ch = (unsigned char)c;

	while (n > 0)
	{
		if (*ptr == ch)
			return (ptr);
		ptr++;
		n--;
	}
	return (0);
	
}

/**
 * The function takes three parameters: a void* pointer s to the memory block, 
 * an int c representing the character to search for, and a size_t n representing
 * the number of bytes to search.
 * 
 * 2. The void* pointer s is cast to an unsigned char* pointer, because we need to work 
 * with individual bytes.
 * 
 * 3. The int c is cast to an unsigned char, because we're looking for this character 
 * in a block of bytes.
 * 
 * 4. A while loop is started that continues as long as n is greater than 0. The n-- > 0 
 * condition checks if n is greater than 0 before decrementing it. This means the loop 
 * will run as long as there are bytes left to search.
 * 
 * 5. Inside the loop, it checks if the byte pointed to by ptr is equal to ch.
 * 
 * 6. If it is, it returns a pointer to this byte. This is the address of the first 
 * occurrence of the character in the memory block.
 * 
 * 7. If it's not, it increments ptr to move to the next byte and decrements n.
 * 
 * 8. If the loop completes without finding the character, it returns NULL to indicate 
 * that the character was not found in the specified memory block.
 * 
 */