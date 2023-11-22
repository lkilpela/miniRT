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

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

static int	ft_is_overflow(long result, int sign, char c)
{
	if (result > INT_MAX / 10 || (result == INT_MAX / 10 && (c - '0') > 7))
	{
		if (sign == 1)
			return (-1);
	}
	else if (result < INT_MIN / 10 || (result == INT_MIN / 10 && (c - '0') > 8))
	{
		if (sign == -1)
			return (0);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		if (ft_is_overflow(result, sign, *str))
		{
			if (sign == 1)
				return (-1);
			if (sign == -1)
				return (0);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}
