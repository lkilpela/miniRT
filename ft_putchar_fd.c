/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:00:16 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/14 12:25:16 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/**
 * The write function in C requires a pointer to the data you want to write as
 * its second argument. This is because write needs to know the location of the
 * data in memory, so it can access and write the correct bytes to the file
 * descriptor.
 * 
 * In your ft_putchar_fd function, c is a single character, not a pointer. So, 
 * to get a pointer to c, you use the address-of operator & to get the address 
 * of c in memory. This is why you pass &c instead of c as the second argument 
 * to write. 
 * 
 * This allows write to access the character c in memory and write it to the 
 * file descriptor fd.
 *
 */