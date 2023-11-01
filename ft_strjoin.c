/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:38:40 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/01 15:11:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates two strings, allocating memory for the result.
 *
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 *
 * @return The concatenated string, or NULL if the allocation fails.
 */

char	*ft_strjoin(char const *s1, char const *s2)
/*{
	char *new_str;
		
	if (s1 == NULL || s2 == NULL)
		return (0);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (0);
	

}*/
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (0);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (new_str == NULL)
		return (0);
	while (i < s1_len)
	{
		new_str[i] = s1[i];
		i++;
	}
	while (j < s2_len)
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}