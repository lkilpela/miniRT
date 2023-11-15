/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:36:57 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/14 11:18:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
	{
		return (NULL);
	}
	ptr = malloc(count * size);
	if (ptr != 0)
	{
		ft_bzero(ptr, count * size);
	}
	return (ptr);
}

/**
 * 1. The function takes two parameters: count and size. count is the number of
 * elements to allocate, and size is the size of each element.
 *
 * 2. It calls malloc to allocate a block of memory of size count * size.
 * This is the total amount of memory needed for count elements, each of size
 * size.
 *

	* 3. If malloc returns a non-null pointer (indicating that the memory
	allocation was successful), it uses bzero to set all bytes in the allocated
	memory to 0.

	* bzero is a function that sets the first n bytes of the area starting at
	ptr to zero (bytes containing '\0').
 *
 * 4. It returns the pointer to the allocated memory.
 * If malloc failed to allocate the memory, this will be a null pointer.
 *
 * This function behaves like the standard calloc function in the C library,
 * allocating memory for an array of count elements, each of size size, and
 * initializing all bytes in the allocated memory to 0.
 *
 */