#include "structs.h"
typedef struct s_world
{
    t_light light;
    t_sphere *spheres;
    int count;
}           t_world;


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

#include <stdbool.h>

bool color_equal(t_color a, t_color b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
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