#include "structs.h"

t_world	*default_world()
{
	t_world *w;

	w = calloc(1, sizeof(t_world));
	if (!w)
		return NULL;
	w->light = point_light(point(-10, 10, -10), color(1, 1, 1));
	w->objects = NULL;
	w->count = 0;
	w->window = create_window(WIDTH, HEIGHT);
	//w->camera = camera(WIDTH, HEIGHT, w->camera.fov);
	w->ambient.ratio = 0.1;
	w->ambient.color = color(1, 1, 1);
	return (w);
}

/**
 * @brief Adds intersections from a temporary array to the main intersections
 * array.
 *
 * This function reallocates memory for the main intersections array to
 * accommodate additional intersections from a temporary array. It then copies
 * the intersections from the temporary array to the main array and updates 
 * the count of intersections.
 *
 * @param xs The main intersections array and its count.
 * @param temp The temporary intersections array and its count.
 * @return The updated main intersections array with the added intersections
 * and updated count.
 */
t_intersections	add_intersections(t_intersections xs, t_intersections temp)
{
	xs.array = realloc(xs.array, (xs.count + temp.count) * sizeof(t_intersection));
	for (int i = 0; i < temp.count; i++) {
		xs.array[xs.count + i] = temp.array[i];
	}
	xs.count += temp.count;
	return (xs);
}

/* COMPARING INTERSECTIONS
** - Purpose: Compares two intersections by their t values.
** - Comparison: Returns -1 if the t value of a is less than the t value of b, 0 if they are equal, and 1 if the t value of a is greater than the t value of b.
** - Parameters: The parameters a and b are pointers to the intersections to be compared.
** - Return: Returns -1 if a->t < b->t, 0 if a->t == b->t, and 1 if a->t > b->t.
** - Note: This function is used by qsort to sort the intersections in ascending order.
*/
int	compare_intersections(const void *a, const void *b)
{
	t_intersection *ia = (t_intersection *)a;
	t_intersection *ib = (t_intersection *)b;
	return ((ia->t > ib->t) - (ia->t < ib->t));
}

/* SORTING INTERSECTIONS
** - Purpose: Sorts the intersections in xs by t value.
** - Sorting: Uses qsort to sort the intersections in xs by t value.
** - Comparison: Uses compare_intersections to compare the t values of two intersections.
** - Sorting Order: The intersections are sorted in ascending order.
*/
void	sort_intersections(t_intersections *xs)
{
	qsort(xs->array, xs->count, sizeof(t_intersection), compare_intersections);
}

/**
 * @brief Computes the intersections of a ray with all objects in the world.
 *
 * This function iterates through all the spheres in the world and computes
 * their intersections with the given ray. It accumulates all intersections
 * into a single `t_intersections` structure, sorts them, and returns the result
 *
 * @param w Pointer to the world containing the objects to intersect.
 * @param r The ray to test for intersections with the objects in the world.
 * @return A `t_intersections` structure containing all intersections of the ray
 *         with the objects in the world, sorted by distance.
 */
t_intersections	intersect_world(t_world *w, t_ray r)
{
	t_intersections	xs;
	t_intersections temp;
	int 			i;

	xs.count = 0;
	xs.array = NULL;
	i = 0;
	while (i < w->count)
	{
		temp = intersect_shape(w->objects[i], r);
		xs = add_intersections(xs, temp);
		free(temp.array);
		i++;
	}
	sort_intersections(&xs);
	return (xs);
}

/* SHADE HIT WITH SHADOWS */
/**
 * @brief Computes the color at a point considering shadows.
 *
 * This function determines if a point is in shadow and then calculates the 
 * resulting color at that point using the lighting model. It also prints 
 * the lighting information for debugging purposes.
 *
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

// Function to compute the color for a given ray
t_color color_at(t_world *world, t_ray r, int x, int y)
{
	t_intersections	xs;
	t_intersection	*hit_p;
	t_color			result;
	t_computations	comps;

	xs = intersect_world(world, r);
	hit_p = hit(&xs);
	if (hit_p)
	{
		comps = prepare_computations(*hit_p, r);
		result = shade_hit_shadow(world, comps);
		print_hit_data(x, y, comps, result, r, hit_p); // DEBUG PRINT
	}
	else
		result = color(0, 0, 0);
	free(xs.array);
	return (result);
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
	t_tuple			v;
	float			distance;
	t_tuple			direction;
	t_ray			r;
	t_intersections	xs;
	t_intersection	*hit_p;

	v = subtract(over_point, w->light.position); // Vector from point to light source
	distance = magnitude(v);
	direction = normalize(v);
	r = ray(w->light.position, direction); // Ray from point to light source
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

void	destroy_world(t_world *w)
{
	if (w == NULL) return;

	if (w->objects)
	{
		for (int i = 0; i < w->count; i++)
		{
			free(w->objects[i]->material);
			free(w->objects[i]->transform);
			//free(w->objects[i]->object);
		}
		free(w->objects);
	}
}
