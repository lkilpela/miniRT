/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:37:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/06 23:10:36 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to check if two tuples are equal
float	dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

// Function to compute the magnitude of a vector
float	magnitude(t_tuple v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

// Function to compute the cross product of two vectors
// The cross product of two vectors is a vector that is perpendicular to both
t_tuple	cross(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	result.w = 0;
	return (result);
}

// Function to normalize a vector
// Normalizing a vector is the process of scaling a vector 
// to have a magnitude of 1
t_tuple	normalize(t_tuple v)
{
	float	mag;

	mag = magnitude(v);
	return (create_tuple(v.x / mag, v.y / mag, v.z / mag, v.w / mag));
}

// Function to reflect a vector
// Reflecting a vector is the process of bouncing a vector off a surface
t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (subtract(in, multiply_by_scalar(normal, 2 * dot(in, normal))));
}
