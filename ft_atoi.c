/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:34:41 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/18 22:14:34 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	
	if (str == NULL)
		return (NULL);
	result = 0;
	sign = 1;
	while (isspace(*str))
	{
		str++;
	}
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

/**
 * 1. The function takes a const char* pointer str to the string to convert.
 *

	* 2. It starts a while loop that continues as long as the current
	character is a
 * whitespace character. This skips any leading whitespace in the string.
 *
 * 3. It then checks if the next character is a sign (- or +). If it's a -,
	it sets
 * sign to -1. If it's a +, it does nothing (since sign is already 1). It then
 * increments str to move to the next character.
 *

	* 4. It starts another while loop that continues as long as the current
	character
 * is a digit. Inside this loop, it multiplies result by 10 and adds the current
 * digit (converted to an integer with *str - '0') to result. It then increments
 * str to move to the next character.
 *
 * 5. Once it has processed all the digits,
	it returns result multiplied by sign.
 * This gives the integer representation of the string, with the correct sign.
 *
 */