/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:46:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 21:51:52 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *origin_array, int origin_count)
{
	char	*resized_array;

	if (origin_count == 0)
	{
		resized_array = malloc(sizeof(char) * 2);
		if (!resized_array)
			return (NULL);
		return (resized_array);
	}
	resized_array = malloc(sizeof(char) * (origin_count * 2));
	if (!resized_array)
		return (NULL);
	if (origin_array)
	{
		ft_memcpy(resized_array, origin_array, sizeof(char) * origin_count);
		free(origin_array);
	}
	return (resized_array);
}
