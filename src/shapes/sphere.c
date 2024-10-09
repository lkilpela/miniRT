/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:08:19 by jlu               #+#    #+#             */
/*   Updated: 2024/10/09 18:38:04 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Sphere's rotation does not affect its shape, so we can ignore it.
static void	sphere_transform(t_shape *sp, t_tuple center, float radius)
{
	t_matrix	translation_matrix;
	t_matrix	scaling_matrix;
	t_matrix	rotation_matrix;

	rotation_matrix = identity_matrix();
	scaling_matrix = scaling(radius, radius, radius);
	translation_matrix = translation(center.x, center.y, center.z);
	chaining_transformations(sp,
		rotation_matrix,
		scaling_matrix,
		translation_matrix);
}

/* SPHERE LOCAL INTERSECTION
** 1. Calculate the coefficients of the quadratic equation
** 2. Calculate the discriminant
** - If the discriminant is less than 0, the ray does not intersect the sphere
** - If the discriminant is 0, the ray intersects the sphere at one point
** - If the discriminant is greater than 0, the ray intersects the sphere at 2p
*/
static t_intersections	local_intersect_sphere(t_shape *shape, t_ray r)
{
	t_sphere		*sp;
	t_coefficients	coeffs;
	t_intersections	result;
	float			discriminant;
	float			t[2];

	sp = (t_sphere *)(shape)->object;
	result.count = 0;
	result.array = NULL;
	coeffs = calculate_sp_coefficients(r, sp);
	discriminant = calculate_discriminant(coeffs);
	if (discriminant < 0)
		return (result);
	else if (discriminant == 0)
	{
		t[0] = -coeffs.b / (2 * coeffs.a);
		result = append_intersection(result, t[0], shape);
	}
	else
	{
		find_intersection_points(discriminant, coeffs, &t[0], &t[1]);
		result = append_intersection(result, t[0], shape);
		result = append_intersection(result, t[1], shape);
	}
	return (result);
}

/* SPHERE NORMALS
** - The normal of a sphere is the same as the point on the sphere
** - Subtract the center of the sphere from the point
*/
static t_tuple	local_normal_at_sphere(t_shape *shape, t_tuple point)
{
	t_sphere	*sp;
	t_tuple		normal;

	sp = (t_sphere *)(shape)->object;
	normal = subtract(point, sp->center);
	return (normal);
}

t_shape	*sphere(t_tuple center, float radius)
{
	t_shape		*object;
	t_sphere	*sp;

	object = shape();
	object->id = SPHERE;
	sp = calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = point(0, 0, 0);
	sp->radius = 1;
	sphere_transform(object, center, radius);
	object->object = sp;
	object->local_intersect = local_intersect_sphere;
	object->local_normal_at = local_normal_at_sphere;
	return (object);
}
