/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:16:53 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/13 13:23:10 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/**
 * 1. Function Definition: The function my_bzero is defined with two
 * parameters:
 * a void* pointer s to the memory area to be filled, and a size_t n that
 * indicates
 * the number of bytes to be set to zero.
 *
 * 2. Using memset: The memset function is used to set each byte in the memory
 * area to zero. The memset function takes three arguments: the pointer to the
 * memory area,
 * the value to set, and the number of bytes to set. In this case,
	the pointer is s,
 * the value is 0 (because we want to set the memory to zero), and the number of
  bytes is n.
 *
 */