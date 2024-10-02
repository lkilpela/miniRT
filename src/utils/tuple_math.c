/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/02 08:56:46 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to add two tuples
t_tuple	add(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}

// Function to subtract two tuples
t_tuple	subtract(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
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

// Function to multiply a tuple by a scalar
t_tuple	multiply_by_scalar(t_tuple t, float scalar)
{
	t_tuple	result;

	result.x = t.x * scalar;
	result.y = t.y * scalar;
	result.z = t.z * scalar;
	result.w = t.w * scalar;
	return (result);
}

// Function to divide two tuples
t_tuple	divide(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	result.w = a.w / b.w;
	return (result);
}
