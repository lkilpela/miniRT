/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:46:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 17:58:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *origin_array, int origin_count, size_t type_size)
{
	void	*resized_array;

	if (origin_count == 0)
	{
		resized_array = malloc(type_size * 2);
		if (!resized_array)
			return (NULL);
		return (resized_array);
	}
	resized_array = malloc(type_size * (origin_count * 2));
	if (!resized_array)
		return (NULL);
	if (origin_array)
	{
		ft_memcpy(resized_array, origin_array, type_size * origin_count);
		free(origin_array);
	}
	return (resized_array);
}
