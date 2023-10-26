/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:19:48 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/26 16:01:10 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int	i;
	
	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);	
}

// Copies the value (unsigned char)ch into each of the 
// first count characters of the object pointed to by dest.
// The behavior is undefined if access occurs beyond the end of the dest array. 
// The behavior is undefined if dest is a null pointer.

// int main()
//{
//    char str[30] = "We are Stdio's Writers";
//    printf("%s\n", str);
//
//    ft_memset(str + 3, '@', 10); 
// set 10 byte từ vị trí thứ 4 của str thành @
//    printf("%s\n", str);
//
//    return 0;
//}