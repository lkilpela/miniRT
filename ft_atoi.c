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
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && (*str - '0') > INT_MAX % 10))
		{
			if (sign == 1)
				return (-1);// overflow
			else if (sign == -1 && (*str - '0') > INT_MAX % 10 + 1)
				return (0);// underflow
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}
