/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 22:36:24 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to add a single intersection directly to result, optimizing memory
t_intersections	append_intersection(t_intersections xs, float t, t_shape *shape)
{
	xs.array = (t_intersection *)ft_realloc((char *)xs.array,
			sizeof(t_intersection) * xs.count);
	if (!xs.array)
		fatal_error("Failed to allocate memory for intersections\n");
	xs.array[xs.count] = intersection(t, shape);
	xs.count++;
	return (xs);
}

// Function to check if a point is within the bounds of the cylinder
bool	check_cap(t_ray r, float t)
{
	float	x;
	float	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (x * x + z * z <= 1);
}

// Function to check if a point is within the bounds of the cylinder
bool	is_within_height_bounds(t_cylinder *cy, t_ray r, float t)
{
	float	y;

	y = r.origin.y + t * r.direction.y;
	return ((cy->minimum < y && y < cy->maximum));
}
