/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumik <lumik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:35:55 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/08 12:24:20 by lumik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int	i;
	
	i = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (i + 1));
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s1, i + 1);
	return (s2);	
}

/**
 * 1. ft_strlen(s1): This gets the length of the input string s1.
 * 
 * 2. malloc(sizeof(char) * (i + 1)): This allocates memory for the new string. 
 * The size is i + 1 to account for the null terminator at the end of the string.
 * 
 * 3. if (s2 == NULL) return (NULL);: This checks if the memory allocation was 
 * successful. If malloc returned NULL, the function returns NULL to indicate 
 * that it couldn't duplicate the string.
 * 
 * 4. ft_memcpy(s2, s1, i + 1);: This copies the input string to the new string. 
 * It copies i + 1 characters to include the null terminator
 * 
 * 5. return (s2);: This returns the new string.
 */