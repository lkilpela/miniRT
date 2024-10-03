/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:57:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/03 10:57:50 by lkilpela         ###   ########.fr       */
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
t_computations prepare_computations(t_intersection i, t_ray r)
{
	t_computations	comps;

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
	comps.over_point = add(comps.point, multiply_by_epsilon(comps.normalv));
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
bool	is_shadowed(t_world *w, t_tuple over_point)
{	
	t_tuple			lightv;
	float			distance;
	t_tuple			light_direction;
	t_ray			r;
	t_intersections	xs;
	t_intersection	*hit_p;

	//lightv = subtract(over_point, w->light.position); // FOR CYLINDER
	
	lightv = subtract(w->light.position, over_point); // FOR SPHERES
	distance = magnitude(lightv);
	light_direction = normalize(lightv);
	r = ray(over_point, light_direction); // FOR SPHERES
	//r = ray(w->light.position, light_direction); // FOR CYLINDER
	xs = intersect_world(w, r);
	hit_p = hit(&xs);
	if (hit_p && hit_p->t < distance)
	{
		free(xs.array);
		return (true); // The point is in shadow
	}
	free(xs.array);
	return (false); // The point is not in shadow
}


/* SHADE HIT WITH SHADOWS */
/**
 * @brief Computes the color at a point considering shadows.
 *
 * This function determines if a point is in shadow and then calculates the 
 * resulting color at that point using the lighting model.
 * @param world A pointer to the world structure containing the light & objects.
 * @param comps A structure containing precomputed values for the intersection.
 * @return The resulting color at the intersection point, considering shadows.
 */
t_color	shade_hit_shadow(t_world *world, t_computations comps) 
{
	bool	in_shadow;
	t_color	result;

	in_shadow = is_shadowed(world, comps.over_point);
	result = lighting_shadow(world, comps.shape->material,
							comps.over_point, comps.eyev, comps.normalv, 
							in_shadow);
	return (result);
}

