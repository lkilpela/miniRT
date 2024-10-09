/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:31:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 19:11:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

static void	cylinder_transform(t_shape *cy, t_tuple center,
						t_tuple axis, double radius)
{
	t_matrix	translation_matrix;
	t_matrix	scaling_matrix;
	t_matrix	rotation_matrix;

	rotation_matrix = rotation(axis, vector(0, 1, 0));
	scaling_matrix = scaling(radius, 1, radius);
	translation_matrix = translation(center.x, center.y, center.z);
	chaining_transformations(cy,
		rotation_matrix,
		scaling_matrix,
		translation_matrix);
}

static t_intersections	intersect_caps(t_shape *shape,
							t_ray r,
							t_intersections result)
{
	t_cylinder		*cy;
	float			t;

	cy = (t_cylinder *)(shape)->object;
	if (fabs(r.direction.y) < EPSILON)
		return (result);
	t = (cy->minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
	{
		result = append_intersection(result, t, shape);
	}
	t = (cy->maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
	{
		result = append_intersection(result, t, shape);
	}
	return (result);
}

/* CY's LOCAL INTERSECTION
** 1. Calculate the coefficients of the quadratic equation
** - If coefficients.a is less than EPSILON, the ray is parallel to the y-axis
** 2. Calculate the discriminant
** - If the discriminant is less than 0, the ray does not intersect the cylinder
** 3. Find the intersection points
** - If the intersection points are within the height bounds of the cylinder,
**   add them to the result
** 4. Check for intersection with the caps
** - If the ray intersects the caps, add the intersection points to the result
*/
static t_intersections	local_intersect_cylinder(t_shape *shape, t_ray r)
{
	t_cylinder		*cy;
	t_intersections	result;
	t_coefficients	coeffs;
	float			discriminant;
	float			t[2];

	cy = (t_cylinder *)(shape)->object;
	result.count = 0;
	result.array = NULL;
	coeffs = calculate_cy_coefficients(r);
	if (coeffs.a < EPSILON)
		return (intersect_caps(shape, r, result));
	discriminant = calculate_discriminant(coeffs);
	if (discriminant < 0)
		return (intersect_caps(shape, r, result));
	find_intersection_points(discriminant, coeffs, &t[0], &t[1]);
	if (is_within_height_bounds(cy, r, t[0]))
		result = append_intersection(result, t[0], shape);
	if (is_within_height_bounds(cy, r, t[1]))
		result = append_intersection(result, t[1], shape);
	result = intersect_caps(shape, r, result);
	return (result);
}

/* CYLINDER NORMALS - COMPUTE SQUARE of DISTANCE from Y AXIS
** 1. If the point is at the top of the cylinder
**   - Return (0, 1, 0)
** 2. If the point is at the bottom of the cylinder
**   - Return (0, -1, 0)
** 3. If the point is on the side of the cylinder
**   - Return (x, 0, z)
*/
static t_tuple	local_normal_at_cylinder(t_shape *shape, t_tuple point)
{
	t_cylinder	*cy;
	float		dist;

	cy = (t_cylinder *)(shape)->object;
	dist = point.x * point.x + point.z * point.z;
	if (dist < 1 && point.y >= cy->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < 1 && point.y <= cy->minimum + EPSILON)
		return (vector(0, -1, 0));
	else
		return (vector(point.x, 0, point.z));
}

t_shape	*cylinder(t_tuple center, t_tuple axis, double radius, double height)
{
	t_shape		*object;
	t_cylinder	*cy;

	object = shape();
	object->id = CYLINDER;
	cy = calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->minimum = - (height / 2);
	cy->maximum = height / 2;
	cylinder_transform(object, center, axis, radius);
	object->object = cy;
	object->local_intersect = local_intersect_cylinder;
	object->local_normal_at = local_normal_at_cylinder;
	return (object);
}
