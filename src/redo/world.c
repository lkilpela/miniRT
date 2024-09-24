#include "structs.h"


t_world *default_world()
{
    t_world *world = calloc(1, sizeof(t_world));
    if (!world)
        return NULL;
    world->light = point_light(point(-10, 10, -10), color(1, 1, 1));

    t_sphere s1 = sphere();
    s1.material = material();
    s1.material.color = color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    t_sphere s2 = sphere();
    s2.transform = scaling(0.5, 0.5, 0.5);

    world->spheres = calloc(2, sizeof(t_sphere));
    world->spheres[0] = s1;
    world->spheres[1] = s2;
    world->count = 2;
    return world;
}


/* COMPARING INTERSECTIONS
** - Purpose: Compares two intersections by their t values.
** - Comparison: Returns -1 if the t value of a is less than the t value of b, 0 if they are equal, and 1 if the t value of a is greater than the t value of b.
** - Parameters: The parameters a and b are pointers to the intersections to be compared.
** - Return: Returns -1 if a->t < b->t, 0 if a->t == b->t, and 1 if a->t > b->t.
** - Note: This function is used by qsort to sort the intersections in ascending order.
*/
int compare_intersections(const void *a, const void *b)
{
    t_intersection *ia = (t_intersection *)a;
    t_intersection *ib = (t_intersection *)b;
    return (ia->t > ib->t) - (ia->t < ib->t);
}

/* SORTING INTERSECTIONS
** - Purpose: Sorts the intersections in xs by t value.
** - Sorting: Uses qsort to sort the intersections in xs by t value.
** - Comparison: Uses compare_intersections to compare the t values of two intersections.
** - Sorting Order: The intersections are sorted in ascending order.
*/
void sort_intersections(t_intersections *xs)
{
    qsort(xs->array, xs->count, sizeof(t_intersection), compare_intersections);
}

/* ADDING INTERSECTIONS
** - Purpose: Combines two t_intersections structures.
** - Reallocation: Uses realloc to resize the array in xs to accommodate the additional intersections from temp.
** - Copying: Copies the intersections from temp into the newly allocated space in xs.
** - Count Update: Updates the count of intersections in xs.
*/
t_intersections add_intersections(t_intersections xs, t_intersections temp)
{
    xs.array = realloc(xs.array, (xs.count + temp.count) * sizeof(t_intersection));
    for (int i = 0; i < temp.count; i++) {
        xs.array[xs.count + i] = temp.array[i];
    }
    xs.count += temp.count;
    return xs;
}

/* INTERSECT WORLD
** - Purpose: Finds the intersections of a ray with all the spheres in the world.
** - Intersections: Loops through all the spheres in the world and finds the intersections of the ray with each sphere.
** - Aggregation: Aggregates the intersections of the ray with all the spheres in the world.
** - Sorting: Sorts the intersections in ascending order by t value.
** - Return: Returns the intersections of the ray with all the spheres in the world.
** - Note: The function allocates memory for the intersections array, which must be freed after use.
** - Note: The function also frees the memory allocated for the intersections of the ray with each sphere.
*/
/**
 * @brief Computes the intersections of a ray with all objects in the world.
 *
 * This function iterates through all the spheres in the world and computes
 * their intersections with the given ray. It accumulates all intersections
 * into a single `t_intersections` structure, sorts them, and returns the result.
 *
 * @param w Pointer to the world containing the objects to intersect.
 * @param r The ray to test for intersections with the objects in the world.
 * @return A `t_intersections` structure containing all intersections of the ray
 *         with the objects in the world, sorted by distance.
 */
t_intersections intersect_world(t_world *w, t_ray r)
{
    t_intersections xs = { .count = 0, .array = NULL };

    for (int i = 0; i < w->count; i++)
    {
        t_intersections temp = intersect_transformation(&w->spheres[i], &r);
        xs = add_intersections(xs, temp);
        free(temp.array);
    }
    sort_intersections(&xs);
    return xs;
}

/**
 * @brief Computes the color at the point of intersection by shading the hit.
 *
 * This function calculates the color at the intersection point by applying the lighting model
 * to the material of the intersected shape, the light source in the world, and the intersection
 * computations.
 *
 * @param world A pointer to the world containing the light source.
 * @param comps The precomputed values for the intersection, including the point of intersection,
 *              the eye vector, and the normal vector.
 * @return The color at the intersection point after applying the lighting model.
 */
t_color shade_hit(t_world *world, t_computations comps) 
{
    t_color result = lighting(&comps.shape->material, &world->light, comps.point, comps.eyev, comps.normalv);

    return result;
}

/* SHADE HIT WITH SHADOWS */
/**
 * @brief Computes the color at a point considering shadows.
 *
 * This function determines if a point is in shadow and then calculates the 
 * resulting color at that point using the lighting model. It also prints 
 * the lighting information for debugging purposes.
 *
 * @param world A pointer to the world structure containing the light and objects.
 * @param comps A structure containing precomputed values for the intersection.
 * @return The resulting color at the intersection point, considering shadows.
 */
t_color shade_hit_shadow(t_world *world, t_computations comps) 
{
    printf(RED "In shade_hit_shadow\n" RESET);
    bool in_shadow = is_shadowed(world, comps.over_point);
    t_color result = lighting_shadow(&comps.shape->material,
                                    &world->light,
                                    comps.over_point, comps.eyev, comps.normalv, 
                                    in_shadow);
    print_lighting_shadow(&comps.shape->material, &world->light, comps.over_point, comps.eyev, comps.normalv, in_shadow);
    return result;
}

// Function to compute the color for a given ray
t_color color_at(t_world *world, t_ray r, int x, int y, t_camera *camera)
{

    t_intersections xs = intersect_world(world, r);
    t_intersection *hit_p = hit(&xs);
    t_color result;
    t_computations comps;
    if (hit_p)
    {
        comps = prepare_computations(*hit_p, r);
        result = shade_hit_shadow(world, comps);
    } else {
        result = color(0, 0, 0); // Black, background color
    }
    print_hit_info(world, &comps, &result, x, y, camera, hit_p);
    free(xs.array);
    return result;
}


/* Function to check if a point is in shadow
** Purpose: Checks if a point is in shadow by measuring the distance to the light source and creating a ray from the point to the light source.
**          The function then intersects the ray with the objects in the world to check if the point is in shadow.
** Parameters: The function takes a pointer to the world and a tuple representing the point to be checked.
            - t_tuple point is intersected by any object in the world.
** Return: Returns true if the point is in shadow, false otherwise.
*/
bool is_shadowed(t_world *world, t_tuple over_point)
{
    // 1. Measure the distance
    // Calculate the vector from the point to the light source
    t_tuple v = subtract(world->light.position, over_point);
    // Find the length of the vector to get the distance
    float distance = magnitude(v);

    // 2. Create a ray
    // Normalize the vector to get the direction
    t_tuple direction = normalize(v);
    // Create a ray from the point to the light source
    t_ray r = ray(over_point, direction);

    // 3. Intersect the world
    // Find the intersections of the ray with objects the world
    t_intersections xs = intersect_world(world, r);

    // 4. Check for shadow
    // Find the hit, if any, that is closer than the distance to light source
    t_intersection *hit_p = hit(&xs);
    if (hit_p && hit_p->t < distance)
    {
        free(xs.array);
        return true; // The point is in shadow
    }
    free(xs.array);
    return false; // The point is not in shadow
}


/*void test_world()
{
    // Test default_world
    t_world *w = default_world();
    assert (w != NULL);
    assert(equal_tuples(w->light.position, point(-10, 10, -10), EPSILON));
    assert(color_equal(w->light.intensity, color(1, 1, 1), EPSILON));
    printf("Passed: Test default_world\n");

    // Test default_world with spheres
    t_sphere s1 = w->spheres[0];
    assert(color_equal(s1.material.color, color(0.8, 1.0, 0.6), EPSILON));
    assert(float_equals(s1.material.diffuse, 0.7, EPSILON));
    assert(float_equals(s1.material.specular, 0.2, EPSILON));


    t_sphere s2 = w->spheres[1];
    assert(matrices_are_equal(s2.transform, scaling(0.5, 0.5, 0.5)));
    printf("Passed: Test default_world with spheres\n");

    // Test intersect_world
    t_world *w1 = default_world();
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_intersections xs = intersect_world(w1, r);
    printf("xs.count: %d\n", xs.count);
    for (int i = 0; i < xs.count; i++) {
        printf("xs.array[%d].t: %f\n", i, xs.array[i].t);
    }

    assert(xs.count == 4);
    assert(float_equals(xs.array[0].t, 4, EPSILON));
    assert(float_equals(xs.array[1].t, 4.5, EPSILON));
    assert(float_equals(xs.array[2].t, 5.5, EPSILON));
    assert(float_equals(xs.array[3].t, 6, EPSILON));
    printf("Passed: Test intersect_world\n");

    free(w);
}

void test_shading()
{
    // Test shading an intersection
    t_world *w = default_world();
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = w->spheres[0];
    t_intersection i = intersection(4, &s);
    assert(i.object == &s);
    t_computations comps = prepare_computations(i, r);
    t_color c = shade_hit(w, comps);
    assert(color_equal(c, color(0.38066, 0.47583, 0.2855), EPSILON));
    printf("Passed: Test shading\n");

    // Test shading with an intersection from inside the object
    w->light = point_light(point(0, 0.25, 0), color(1, 1, 1));
    t_ray r1 = ray(point(0, 0, 0), vector(0, 0, 1));
    t_sphere s1 = w->spheres[1];
    t_intersection i1 = intersection(0.5, &s1);
    t_computations comps1 = prepare_computations(i1, r1);
    t_color c1 = shade_hit(w, comps1);
    assert(color_equal(c1, color(0.90498, 0.90498, 0.90498), EPSILON));
    printf("Passed: Test shading inside\n");

    // The color when a ray misses
    t_ray r2 = ray(point(0, 0, -5), vector(0, 1, 0));
    t_color c2 = color_at(w, r2);
    assert(color_equal(c2, color(0, 0, 0), EPSILON));
    printf("Passed: Test color when ray misses\n");

    // The color with an intersection behind the ray
    t_world *w1 = default_world();
    t_sphere outer = w1->spheres[0];
    outer.material.ambient = 1;
    t_sphere inner = w1->spheres[1];
    inner.material.ambient = 1;
    t_ray r3 = ray(point(0, 0, 0.75), vector(0, 0, -1));
    t_color c3 = color_at(w1, r3);
    printf("Inner color: \n");
    print_color(inner.material.color);
    printf("Color: \n");
    print_color(c3);
    assert(color_equal(c3, inner.material.color, EPSILON));
    printf("Passed: Test color with intersection behind ray\n");
    
    free(w);
    free(w1);

}*/

void test_is_shadowed()
{
    // Test is_shadowed with no objects between the point and the light
    t_world *w = default_world();
    t_tuple p = point(0, 10, 0);
    assert(!is_shadowed(w, p));
    printf("Passed: Test is_shadowed with no objects between the point and the light\n");

    // Test is_shadowed with an object between the point and the light
    t_tuple p1 = point(10, -10, 10);
    assert(is_shadowed(w, p1));
    printf("Passed: Test is_shadowed with an object between the point and the light\n");

    // Test is_shadowed with an object between the point and the light
    t_tuple p2 = point(-20, 20, -20);
    assert(!is_shadowed(w, p2));
    printf("Passed: Test is_shadowed with no objects between the point and the light\n");

    // Test is_shadowed with an object between the point and the light
    t_tuple p3 = point(-2, 2, -2);
    assert(!is_shadowed(w, p3));
    printf("Passed: Test is_shadowed with no objects between the point and the light\n");

    free(w);
}

void test_render_shadow()
{
    // shade_hit() is given an intersection in shadow

    t_world *w = default_world();
    w->light = point_light(point(0, 0, -10), color(1, 1, 1));
    //t_sphere s1 = w->spheres[1];
    t_sphere s2 = w->spheres[2];
    s2.transform = translation(0, 0, 10);
    t_ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    t_intersection i = intersection(4, &s2);
    t_computations comps = prepare_computations(i, r);
    t_color result = shade_hit_shadow(w, comps);
    print_color(result);
    //assert(color_equal(result, color(0.1, 0.1, 0.1), EPSILON));
    //printf("Passed: Test shade_hit() with an intersection in shadow\n"); 

}