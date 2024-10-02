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
	int				i;

	hit = NULL;
	i = 0;
	if (intersections == NULL)
		return (NULL);
	while (i < intersections->count)
	{
		if (intersections->array[i].t >= 0)
		{
			if (hit == NULL || intersections->array[i].t < hit->t)
			{
				hit = &intersections->array[i];
			}
		}
		i++;
	}
	return (hit);
}

