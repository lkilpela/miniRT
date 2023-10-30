/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:31:47 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/30 14:00:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
     unsigned char	*temp_s1;
     unsigned char	*temp_s2;

     temp_s1 = (unsigned char *)s1;
     temp_s2 = (unsigned char *)s2;

     while (n > 0)
     {
          if (*temp_s1 != *temp_s2)
               return ((int)*temp_s1 - (int)*temp_s2);
          --n;
          ++temp_s1;
          ++temp_s2;
     }
     return (0);
}

/*
DESCRIPTION
     The memcmp() function compares byte string s1 against byte string s2.  Both strings
     are assumed to be n bytes long.

RETURN VALUES
     The memcmp() function returns zero if the two strings are identical, otherwise returns
     the difference between the first two differing bytes (treated as unsigned char values,
     so that `\200' is greater than `\0', for example).  Zero-length strings are always
     identical.  This behavior is not required by C and portable code should only depend on
     the sign of the returned value.

// need to type cast the difference value of two strings to type (int) because  
since they are unsigned, result is always positive, 
even if the right hand side bigger
*/