/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/06 22:51:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to check if a point is within the bounds of the cylinder
bool	check_cap(t_ray r, float t)
{
	float	x;
	float	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (x * x + z * z <= 1);
}

// Returns the angle between an axis and the vector 
// from the origin to the point
float	calculate_angle(float a, float b)
{
	float	angle;

	angle = atan2(a, b);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	free_intersections(t_intersections *intersections)
{
	free(intersections->array);
}

bool	is_within_height_bounds(t_cylinder *cy, t_ray r, float t)
{
    float	y;

	y = r.origin.y + t * r.direction.y;
    return ((cy->minimum < y && y < cy->maximum));
}

float	calculate_discriminant(t_coefficients coeffs)
{
	float	disc;
	disc = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
	return (disc);
}