/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:09:50 by jlu               #+#    #+#             */
/*   Updated: 2024/10/07 14:30:41 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to negate a tuple
// Negating a tuple is the same as multiplying it by -1
t_tuple	negate(t_tuple t)
{
	t_tuple	result;

	result.x = -t.x;
	result.y = -t.y;
	result.z = -t.z;
	result.w = -t.w;
	return (result);
}

// Calculate an adaptive epsilon
// based on the scale of the scene or the distance from the camera
double	adaptive_epsilon(t_tuple point)
{
	return (EPSILON * fmax(fabs(point.x), fmax(fabs(point.y), fabs(point.z))));
}

// Function to multiply a tuple by an adaptive epsilon
t_tuple	multiply_by_epsilon(t_tuple t)
{
	t_tuple	result;

	result.x = t.x * adaptive_epsilon(t);
	result.y = t.y * adaptive_epsilon(t);
	result.z = t.z * adaptive_epsilon(t);
	result.w = t.w * adaptive_epsilon(t);
	return (result);
}
