/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:34:41 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/31 11:37:15 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' 
		|| c == '\f' || c == '\r'  || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res = 0;
	int	i = 0;
	int	sign = 1;

	while (ft_isspace(str[i]) != 0)
	{
		i++;
	}
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res*10 + str[i] - '0';
		i++;
	}
	return (sign*res);
}
