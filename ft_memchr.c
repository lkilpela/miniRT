/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:30:19 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/30 12:57:36 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void *ft_memchr(const void *s, int c, size_t n)
{
     unsigned char  *temp;
     
     temp = (unsigned char *)s;
     while (n > 0)
     {
          if (*temp == (unsigned char)c)
               return (temp);
          ++temp;
          --n;
     }
    return (0);  
}

/*
The memchr() function locates the first occurrence of c (converted to an unsigned
     char) in string s.

RETURN VALUES
     The memchr() function returns a pointer to the byte located, or NULL if no such byte
     exists within n bytes.
	 
*/