/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:57:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 00:05:51 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

/* PREPARE COMPUTATIONS FOR SHADING 
** 1. Copy the intersection's properties, for convenience
** 2. Precompute some useful values
** 3. If the dot product is negative, the normal is inverted
**  when the intersection is inside an object -> surface is illuminated properly
** 4. Compute over_point to avoid shadow acne
**   - By applying a small offset to the intersection point in
**   the direction of the normal vector -> move the point slightly away 
**	 from the surface.
*/
t_computations	prepare_computations(t_intersection i, t_ray r)
{
	t_computations	comps;
	t_tuple			offset;

	comps.t = i.t;
	comps.shape = i.object;
	comps.point = position(r, comps.t);
	comps.eyev = negate(r.direction);
	comps.normalv = normal_at_shape(comps.shape, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate(comps.normalv);
	}
	else
		comps.inside = false;
	offset = multiply_by_epsilon(comps.normalv);
	comps.over_point = add(comps.point, offset);
	return (comps);
}

/* Function to check if a point is in shadow
** 1. Measure the distance
**   - Calculate the vector from the point to the light source
**   - Find the length of the vector to get the distance
** 2. Create a ray
**   - Normalize the vector to get the direction
**  - Create a ray from the point to the light source
** 3. Intersect the world
**   - Find the intersections of the ray with objects the world
** 4. Check for shadow
**   - Find the hit, if any, that is closer than the distance to light source
*/
static bool	is_shadowed(t_world *w, t_computations comps)
{
	t_tuple			lightv;
	t_ray			r;
	float			distance;
	t_intersections	xs;
	t_intersection	*hit_p;

	lightv = subtract(w->light.position, comps.over_point);
	distance = magnitude(lightv);
	r = ray(comps.over_point, normalize(lightv));
	xs = intersect_world(w, r);
	hit_p = hit(&xs);
	if (hit_p && hit_p->t > 0 && hit_p->t < distance)
	{
		free(xs.array);
		return (true);
	}
	free(xs.array);
	return (false);
}

// Function to shade a hit and check for shadows
t_color	shade_hit(t_world *world, t_computations comps)
{
	bool	in_shadow;
	t_color	result;

	in_shadow = is_shadowed(world, comps);
	result = lighting(world, comps, comps.shape->material, in_shadow);
	return (result);
}
