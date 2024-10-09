/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:58:49 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 18:59:01 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to create a new world
t_world	*default_world(void)
{
	t_world	*w;

	w = calloc(1, sizeof(t_world));
	if (!w)
		return (NULL);
	w->light = point_light(point(-10, 10, -10), color(1, 1, 1));
	w->objects = NULL;
	w->count = 0;
	w->window = create_window(WIDTH, HEIGHT, w);
	w->ambient.ratio = 0.1;
	w->ambient.color = color(1, 1, 1);
	return (w);
}

/* ADDING INTERSECTIONS
*/
static t_intersections	add_intersections(t_intersections xs,
							t_intersections temp)
{
	int	i;

	xs.array = (t_intersection *)ft_realloc(xs.array,
			sizeof(t_intersection) * xs.count,
			sizeof(t_intersection) * (xs.count + temp.count));
	if (!xs.array)
	{
		ft_printf("Error: Memory allocation failed in add_intersections\n");
		return (xs);
	}
	i = 0;
	while (i < temp.count)
	{
		xs.array[xs.count + i] = temp.array[i];
		i++;
	}
	xs.count += temp.count;
	return (xs);
}

/* COMPARING INTERSECTIONS
** - Purpose: Compares two intersections by their t values.
** - Comparison: Returns -1 if the t value of a is less than the t value of b, 
** 0 if they are equal, and 1 if t value of a is greater than t value of b.
** - Params: Parameters a and b are pointers to intersections to be compared.
** - Return: Returns -1 if a->t < b->t, 0 if a->t == b->t, and 1 if a->t > b->t.
** - This function is used by qsort to sort intersections in ascending order.
*/
static int	compare_intersections(const void *a, const void *b)
{
	t_intersection	*ia;
	t_intersection	*ib;

	ia = (t_intersection *)a;
	ib = (t_intersection *)b;
	return ((ia->t > ib->t) - (ia->t < ib->t));
}

/* SORTING INTERSECTIONS
** - Purpose: Sorts the intersections in xs by t value.
** - Sorting: Uses qsort to sort the intersections in xs by t value.
** - Uses compare_intersections to compare the t values of two intersections.
** - Sorting Order: The intersections are sorted in ascending order.
*/
static void	sort_intersections(t_intersections *xs)
{
	qsort(xs->array, xs->count, sizeof(t_intersection), compare_intersections);
}

/* INTERSECT WORLD
** 1. Initialize an empty list of intersections
** 2. Loop through all objects in the world
** 3. Intersect the object with the ray
** 4. If the object intersects, add the intersections to the list
** 5. Sort the intersections by t value
*/
t_intersections	intersect_world(t_world *w, t_ray r)
{
	t_intersections	xs;
	t_intersections	temp;
	int				i;

	xs.count = 0;
	xs.array = NULL;
	i = 0;
	while (i < w->count)
	{
		temp = intersect_shape(w->objects[i], r);
		if (temp.count > 0)
			xs = add_intersections(xs, temp);
		free(temp.array);
		i++;
	}
	sort_intersections(&xs);
	return (xs);
}
