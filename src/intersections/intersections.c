/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:18 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 19:10:57 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Create an intersection object with a given t value and the intersected object
t_intersection	intersection(float t, t_shape *shape)
{
	t_intersection	i;

	i.t = t;
	i.object = shape;
	return (i);
}

// Function to add a single intersection directly to result, optimizing memory
t_intersections	append_intersection(t_intersections xs, float t, t_shape *shape)
{
	xs.array = (t_intersection *)ft_realloc(xs.array,
			xs.count * sizeof(t_intersection),
			(xs.count + 1) * sizeof(t_intersection));
	if (!xs.array)
		fatal_error("Failed to allocate memory for intersections\n");
	xs.array[xs.count] = intersection(t, shape);
	xs.count++;
	return (xs);
}

/* HIT 
** Loop through all intersections and return the intersection with
** the lowest positive t value
** If there are no positive t values, return NULL
*/
t_intersection	*hit(t_intersections *intersections)
{
	t_intersection	*hit;
	int				i;

	hit = NULL;
	i = 0;
	if (!intersections)
		return (NULL);
	while (i < intersections->count)
	{
		if (intersections->array[i].t >= 0)
		{
			if (!hit || intersections->array[i].t < hit->t)
			{
				hit = &intersections->array[i];
			}
		}
		i++;
	}
	return (hit);
}
