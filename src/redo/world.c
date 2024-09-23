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
    t_color result = lighting(&comps.shape->material, &world->light, comps.point, comps.eyev, comps.normalv);
    //print_lighting(&world->light, &result, comps.point, comps.eyev, comps.normalv);
    return result;
}
void print_hit_info(t_world *world, t_computations *comps, t_color *result, int x, int y, t_camera *camera, t_intersection *hit_p)
{
    // Print hit information at key pixels
    if ((x == camera->hsize / 2 && y == camera->vsize / 2) || // Center
        (x == 0 && y == 0) || // Top-Left Corner
        (x == camera->hsize - 1 && y == 0) || // Top-Right Corner
        (x == 0 && y == camera->vsize - 1) || // Bottom-Left Corner
        (x == camera->hsize - 1 && y == camera->vsize - 1)) { // Bottom-Right Corner

        printf("Hit at key pixel (%d, %d): t = %f\n", x, y, hit_p->t);
        print_lighting(&world->light, result, comps->point, comps->eyev, comps->normalv);
        print_color(*result);
        
    }
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
        result = shade_hit(world, comps);
    } else {
        result = color(0, 0, 0); // Black, background color
    }
    print_hit_info(world, &comps, &result, x, y, camera, hit_p);
    free(xs.array);
    return result;
}

// Function to create the scene
t_world *create_scene()
{
    t_world *world = default_world();

    // Floor
    t_sphere floor = sphere();
    floor.transform = scaling(10, 0.01, 10);
    floor.material = material();
    floor.material.color = color(1, 0.9, 0.9);
    floor.material.specular = 0;

    // Left wall
    t_sphere left_wall = sphere();
    left_wall.transform = multiply_matrices(
        multiply_matrices(
            multiply_matrices(
                translation(0, 0, 5),
                rotation_y(-M_PI / 4)
            ),
            rotation_x(M_PI / 2)
        ),
        scaling(10, 0.01, 10)
    );
    left_wall.material = floor.material;

    // Right wall
    t_sphere right_wall = sphere();
    right_wall.transform = multiply_matrices(
        multiply_matrices(
            multiply_matrices(
                translation(0, 0, 5),
                rotation_y(M_PI / 4)
            ),
            rotation_x(M_PI / 2)
        ),
        scaling(10, 0.01, 10)
    );
    right_wall.material = floor.material;

    // Middle sphere
    t_sphere middle = sphere();
    middle.transform = translation(-0.5, 1, 0.5);
    middle.material = material();
    middle.material.color = color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    // Right sphere
    t_sphere right = sphere();
    right.transform = multiply_matrices(
        translation(1.5, 0.5, -0.5),
        scaling(0.5, 0.5, 0.5)
    );
    right.material = material();
    right.material.color = color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    // Left sphere
    t_sphere left = sphere();
    left.transform = multiply_matrices(
        translation(-1.5, 0.33, -0.75),
        scaling(0.33, 0.33, 0.33)
    );
    left.material = material();
    left.material.color = color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    // Add spheres to the world
    world->spheres = calloc(6, sizeof(t_sphere));
    world->spheres[0] = floor;
    world->spheres[1] = left_wall;
    world->spheres[2] = right_wall;
    world->spheres[3] = middle;
    world->spheres[4] = right;
    world->spheres[5] = left;
    world->count = 6;


    return world;
}
/*

void test_world()
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