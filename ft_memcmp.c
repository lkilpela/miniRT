/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:31:47 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/08 10:38:05 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
     unsigned char *ptr1;
     unsigned char *ptr2;

     ptr1 = (unsigned char *)s1;
     ptr2 = (unsigned char *)s2;

     while (n > 0)
     {
          if (*ptr1 != *ptr2)
               return (*ptr1 - *ptr2);
          ptr1++;
          ptr2++;
          n--;
     }
     return (0);
}

/**
 * 1. The function takes three parameters: two void* pointers s1 and s2 to the memory
 * blocks to compare, and a size_t n representing the number of bytes to compare.
 * 
 * 2. The void* pointers s1 and s2 are cast to unsigned char* pointers, because we n
 * need to work with individual bytes. 
 * 
 * 3. A while loop is started that continues as long as n is greater than 0. 
 * The n-- > 0 condition checks if n is greater than 0 before decrementing it. 
 * This means the loop will run as long as there are bytes left to compare.
 * 
 * 4. Inside the loop, it checks if the byte pointed to by ptr1 is not equal to the 
 * byte pointed to by ptr2.
 * 
 * 5. If they are not equal, it returns the difference between the two bytes. 
 * This will be a positive number if the byte in s1 is greater than the byte in s2,
 * and a negative number if it's less.
 * 
 * 6. If the bytes are equal, it increments both ptr1 and ptr2 to move to the next byte 
 * in each memory block, and decrements n.
 * 
 * 7. If the loop completes without finding any differing bytes, it returns 0 to indicate
 * that the two memory blocks are equal.
 */