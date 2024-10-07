/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:47:53 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:47:55 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Create a ray with an origin and a direction
t_ray	ray(t_tuple origin, t_tuple direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

// Calulate the point at given distance t along the ray
// - Multiply ray's direction by t -> Gives total distance traveled
// - Add that to ray's origin -> Gives final position
t_tuple	position(t_ray r, float t)
{
	t_tuple	result;

	result = add(r.origin, multiply_by_scalar(r.direction, t));
	return (result);
}

// Translating a ray
t_ray	transform(t_ray r, t_matrix m)
{
	t_ray	transformed_ray;
	t_tuple	direction;

	transformed_ray.origin = matrix_multiply_tuple(m, r.origin);
	direction = r.direction;
	direction.w = 0;
	transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
	return (transformed_ray);
}
