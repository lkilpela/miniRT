/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:12:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 22:51:58 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to calculate the discriminant of a quadratic equation
float	calculate_discriminant(t_coefficients coeffs)
{
	float	disc;

	disc = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
	return (disc);
}

// Function to calculate the coefficients of a quadratic equation
t_coefficients	calculate_cy_coefficients(t_ray r)
{
	t_coefficients	coeffs;

	coeffs.a = (r.direction.x * r.direction.x)
		+ (r.direction.z * r.direction.z);
	coeffs.b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	coeffs.c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
	return (coeffs);
}

t_coefficients	calculate_sp_coefficients(t_ray r, t_sphere *sp)
{
	t_coefficients	coeffs;
	t_tuple			sphere_to_ray;

	sphere_to_ray = subtract(r.origin, sp->center);
	coeffs.a = dot(r.direction, r.direction);
	coeffs.b = 2 * dot(r.direction, sphere_to_ray);
	coeffs.c = dot(sphere_to_ray, sphere_to_ray) - sp->radius * sp->radius;
	return (coeffs);
}

// Function to find the intersection points of a quadratic equation
void	find_intersection_points(float disc, t_coefficients coeffs,
									float *t0, float *t1)
{
	*t0 = (-coeffs.b - sqrt(disc)) / (2 * coeffs.a);
	*t1 = (-coeffs.b + sqrt(disc)) / (2 * coeffs.a);
	if (*t0 > *t1)
		ft_swap(t0, t1);
}
