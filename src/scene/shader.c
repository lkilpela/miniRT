/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:57:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/03 12:07:20 by lkilpela         ###   ########.fr       */
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
bool	is_shadowed(t_world *w, t_computations comps)
{	
	t_tuple			lightv;
	float			distance;
	t_tuple			light_direction;
	t_ray			r;
	t_intersections	xs;
	t_intersection	*hit_p;

	lightv = subtract(w->light.position, comps.over_point);
	distance = magnitude(lightv);
	light_direction = normalize(lightv);
	r = ray(comps.over_point, light_direction);
	xs = intersect_world(w, r);
	hit_p = hit(&xs);
	if (hit_p && hit_p->t > 0 && hit_p->t < distance)
	{

		//printf(RED "SHADOW " RESET "%f - %f\n" , hit_p->t, distance);
		printf(YELLOW "OVER POINT " RESET "%f %f %f\n", comps.over_point.x, comps.over_point.y, comps.over_point.z);
		//printf(GREEN "POINT " RESET "%f %f %f\n", comps.point.x, comps.point.y, comps.point.z);
		//printf(BLUE "RAY DIRECTION " RESET "%f %f %f\n", r.direction.x, r.direction.y, r.direction.z);
		printf(GREEN "NORMAL " RESET "%f %f %f\n", comps.normalv.x, comps.normalv.y, comps.normalv.z);
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
t_color	shade_hit(t_world *world, t_computations comps) 
{
	bool	in_shadow;
	t_color	result;

	in_shadow = is_shadowed(world, comps);
	result = lighting(world, comps, comps.shape->material, in_shadow);
	return (result);
}

