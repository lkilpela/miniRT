/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:01:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/06 14:12:24 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

float	ft_atof(const char *str)
{
	float	res;
	float	dec;
	int		sign;

	res = 0;
	dec = 0.1f;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		res += (*str++ - '0') * dec;
		dec /= 10;
	}
	return (res * sign);
}
