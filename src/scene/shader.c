/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:57:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/02 14:57:16 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

/* PREPARE COMPUTATIONS FOR SHADING 
** 1. Copy the intersection's properties, for convenience
** 2. Precompute some useful values
** 3. If the dot product is negative, the normal points inwards
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
