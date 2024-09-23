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

void print_lighting(t_light *light, t_color *color, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    printf("Lighting: \n");
    printf("Light position: \n");
    print_tuple(light->position);
    printf("Color: \n");
    print_color(*color);
    printf("Point: \n");
    print_tuple(point);
    printf("Eye vector: \n");
    print_tuple(eyev);
    printf("Normal vector: \n");
    print_tuple(normalv);
}

/* SHADE HIT
** - Return: Returns the color at the intersection encapsulated by computations, in the given world.
*/
t_color shade_hit(t_world *world, t_computations comps) 
{
    //print_lighting(&world->light, &world->light.intensity, comps.point, comps.eyev, comps.normalv);
    t_color result = lighting(&comps.shape->material, &world->light, comps.point, comps.eyev, comps.normalv);
    printf("Material color: ");
    print_color(comps.shape->material.color);
    printf("World light intensity: ");
    print_color(world->light.intensity);
    return result;
}

// Function to compute the color for a given ray
t_color color_at(t_world *world, t_ray r)
{
    t_intersections xs = intersect_world(world, r);
    t_intersection *hit_p = hit(&xs);
    t_color result;
    if (hit_p)
    {
        t_computations comps = prepare_computations(*hit_p, r);
        result = shade_hit(world, comps);
    } else {
        result = color(0, 0, 0); // Black, background color
    }
    free(xs.array);
    return result;
}

void test_world()
{
    // Test default_world
    t_world *w = default_world();
    assert (w != NULL);
    assert(equal_tuples(w->light.position, point(-10, 10, -10), EPSILON));
    assert(color_equal(w->light.intensity, color(1, 1, 1)));
    printf("Passed: Test default_world\n");

    // Test default_world with spheres
    t_sphere s1 = w->spheres[0];
    assert(color_equal(s1.material.color, color(0.8, 1.0, 0.6)));
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



    //printf("Comps values in test_shading: \n");
    //print_tuple(comps.point);
    //print_tuple(comps.eyev);
    //print_tuple(comps.normalv);

    //printf("Sphere color: ");
    //print_color(s.material.color);
    //printf("Intersection color: ");
    //print_color(i.object->material.color);
    //printf("Comps object color: ");
    //print_color(comps.object->material.color);
    t_color c = shade_hit(w, comps);
   
    printf("0. Shading an intersection: ");
    print_color(c);
   // assert(color_equal(c, color(0.38066, 0.47583, 0.2855)));
    //printf("Passed: Test shading\n");

    // Test shading with an intersection from inside the object
    w->light = point_light(point(0, 0.25, 0), color(1, 1, 1));
    t_ray r1 = ray(point(0, 0, 0), vector(0, 0, 1));
    t_sphere s1 = w->spheres[1];
    t_intersection i1 = intersection(0.5, &s1);
    t_computations comps1 = prepare_computations(i1, r1);
    t_color c1 = shade_hit(w, comps1);
    printf("1. Shading inside: ");
    print_color(c1);
    //assert(color_equal(c1, color(0.90498, 0.90498, 0.90498)));
    //printf("Passed: Test shading inside\n");

    // The color when a ray misses
    t_ray r2 = ray(point(0, 0, -5), vector(0, 1, 0));
    t_color c2 = color_at(w, r2);
    printf("2. Color when ray misses: ");
    print_color(c2);
    //assert(color_equal(c2, color(0.38066, 0.47583, 0.2855)));
    //printf("Passed: Test color when ray misses\n");

    // The color with an intersection behind the ray
    t_world *w1 = default_world();
    t_sphere outer = w1->spheres[0];
    outer.material.ambient = 1;
    t_sphere inner = w1->spheres[1];
    inner.material.ambient = 1;
    t_ray r3 = ray(point(0, 0, 0.75), vector(0, 0, -1));
    t_color c3 = color_at(w1, r3);
    printf("3. Color with intersection behind ray: ");
    print_color(c3);
    //t_color inner_color = color(0.90498, 0.90498, 0.90498);
    //assert(color_equal(c3, inner.material.color));
    //printf("Passed: Test color with intersection behind ray\n");
    
    free(w);
    free(w1);

}