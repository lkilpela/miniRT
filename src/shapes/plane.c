/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:23:53 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 18:37:02 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Scaling is generally not necessary for a plane because a plane is infinite
// in extent and scaling it doesn't change its appearance or properties.
static void	plane_transform(t_shape *sp, t_tuple p, t_tuple normal)
{
	t_matrix	translation_matrix;
	t_matrix	scaling_matrix;
	t_matrix	rotation_matrix;

	rotation_matrix = rotation(normal, vector(0, 1, 0));
	scaling_matrix = scaling(1, 1, 1);
	translation_matrix = translation(p.x, p.y, p.z);
	chaining_transformations(sp,
		rotation_matrix,
		scaling_matrix,
		translation_matrix);
}

/* PLANE LOCAL INTERSECTION
** 1. If ray is smaller than EPSILON, means it is parallel to the plane
** 2. Calculate the intersection point
**   - Distance = -origin.y / direction.y
** 3. Add the intersection point to the result
*/
static t_intersections	local_intersect_plane(t_shape *shape, t_ray r)
{
	t_intersections	result;
	float			t;

	result.count = 0;
	result.array = NULL;
	if (fabs(r.direction.y) < EPSILON)
		return (result);
	t = -r.origin.y / r.direction.y;
	result = append_intersection(result, t, shape);
	return (result);
}

/* PLANE NORMALS
** - The normal of a plane is the same everywhere, vector(0, 1, 0)
*/
static t_tuple	local_normal_at_plane(t_shape *shape, t_tuple point)
{
	(void)point;
	(void)shape;
	return (vector(0, 1, 0));
}

// Create a plane
t_shape	*plane(t_tuple p, t_tuple normal)
{
	t_shape	*object;
	t_plane	*pl;

	object = shape();
	object->id = PLANE;
	pl = calloc(1, sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->p = p;
	pl->normal = normal;
	plane_transform(object, p, normal);
	object->object = pl;
	object->local_intersect = local_intersect_plane;
	object->local_normal_at = local_normal_at_plane;
	return (object);
}
