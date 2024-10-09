/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:27:54 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 18:39:40 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Create a new shape
t_shape	*shape(void)
{
	t_shape	*object;

	object = calloc(1, sizeof(t_shape));
	if (!object)
		return (NULL);
	object->id = 0;
	object->transform = identity_matrix();
	object->material = material();
	object->object = NULL;
	object->local_normal_at = NULL;
	object->local_intersect = NULL;
	return (object);
}

static bool	is_zero_vector(t_tuple t)
{
	return (t.x == 0 && t.y == 0 && t.z == 0 && t.w == 0);
}

static bool	is_valid_ray(t_ray ray)
{
	return (!(is_zero_vector(ray.origin) && is_zero_vector(ray.direction)));
}

t_intersections	intersect_shape(t_shape *shape, t_ray ray)
{
	t_matrix	inverse_transform;
	t_ray		local_ray;

	if (!shape || !is_valid_ray(ray))
		fatal_error("Intersect_shape: shape or ray is NULL\n");
	if (!shape->local_intersect)
		fatal_error("Intersect_shape: local_intersect is NULL\n");
	inverse_transform = inverse(shape->transform);
	local_ray = transform(ray, inverse_transform);
	return (shape->local_intersect(shape, local_ray));
}

/* NORMAL AT SHAPE
** 1. Transform the point to object space
** - Inverse of the transformation matrix
** - Multiply the point by the inverse
** 2. Compute the normal in object space
** - Call the local_normal_at function
** 3. Transform the normal to world space
** - Transpose the inverse of the transformation matrix
** - Multiply the normal by the transpose inverse
** - Set the w component to 0
*/
t_tuple	normal_at_shape(t_shape *shape, t_tuple world_point)
{
	t_matrix	inverse_transform;
	t_tuple		local_point;
	t_tuple		local_normal;
	t_matrix	transpose_inverse_transform;
	t_tuple		world_normal;

	if (!shape)
		fatal_error("Normal_at_shape: shape is NULL\n");
	inverse_transform = inverse(shape->transform);
	local_point = matrix_multiply_tuple(inverse_transform, world_point);
	local_normal = shape->local_normal_at(shape, local_point);
	transpose_inverse_transform = transpose_matrix(inverse_transform);
	world_normal = matrix_multiply_tuple(transpose_inverse_transform,
			local_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}
