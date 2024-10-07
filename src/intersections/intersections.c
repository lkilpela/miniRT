/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:02:18 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:49:13 by lkilpela         ###   ########.fr       */
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

// Aggregates intersections into a collection of intersections
t_intersections	intersections_array(int count, t_intersection *array)
{
	t_intersections	xs;
	int				i;

	if (array != NULL)
	{
		xs.count = count;
		xs.array = calloc(count, sizeof(t_intersection));
		if (!xs.array)
			fatal_error("Failed to allocate memory for intersections_array\n");
		i = 0;
		while (i < count)
		{
			xs.array[i] = array[i];
			i++;
		}
	}
	else
	{
		xs.count = 0;
		xs.array = NULL;
	}
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
