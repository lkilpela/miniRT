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
/* - Purpose: Creates a new t_intersections structure with a specified count.
** - Allocation: Uses calloc to allocate memory for the array in xs.
** - Initialization: Initializes the array with either the provided intersections or default values.
** - Count Setting: Sets the count of intersections in xs.
*/
t_intersections	intersections_array(int count, t_intersection *array)
{
	t_intersections	xs;
	int				i;

	if (array != NULL)
	{
		xs.count = count;
		xs.array = calloc(count, sizeof(t_intersection));
		if (xs.array == NULL)
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
** Loop through all intersections and return the intersection with the lowest positive t value
** If there are no positive t values, return NULL
*/
t_intersection	*hit(t_intersections *intersections)
{
	t_intersection	*hit;

	hit = NULL;
	for (int i = 0; i < intersections->count; i++)
	{
		if (intersections->array[i].t >= 0)
		{
			if (hit == NULL || intersections->array[i].t < hit->t)
			{
				hit = &intersections->array[i];
			}
		}
	}
	return (hit);
}

/* PREPARE COMPUTATIONS
** - Purpose: the computations for shading
** 1. Copy the intersection's properties, for convenience
** 2. Precompute some useful values
** 3. If the dot product is negative, the normal points inwards
** 4. Compute over_point to avoid shadow acne
**   - EPSILON is a small number, 1e-6. Is used here to bump the point just a bit in the direction of the normal.
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
