/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:07:22 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:34:39 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_color	multiply_color(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r * c2.r;
	result.g = c1.g * c2.g;
	result.b = c1.b * c2.b;
	return (result);
}

t_color	multiply_color_by_scalar(t_color c, float scalar)
{
	t_color	result;

	result.r = c.r * scalar;
	result.g = c.g * scalar;
	result.b = c.b * scalar;
	return (result);
}

t_color	add_color(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	return (result);
}

// Clamp the color to prevent the color from exceeding the maximum value of 1.0
void	clamp_color(t_color *c)
{
	if (c->r > 1.0)
		c->r = 1.0;
	if (c->g > 1.0)
		c->g = 1.0;
	if (c->b > 1.0)
		c->b = 1.0;
}
