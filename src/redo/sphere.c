#include "structs.h"

t_sphere sphere()
{
    t_sphere s;

    s.center = point(0, 0, 0);
    s.radius = 1;
    s.transform = identity_matrix(4);
    s.material = material();
    return (s);
}

// Create an intersection object with a given t value and the intersected object
t_intersection intersection(float t, void *object)
{
    t_intersection i;

    i.t = t;
    i.object = object;
    return (i);
}


// Aggregates intersections into a collection of intersections
/* - Purpose: Creates a new t_intersections structure with a specified count.
** - Allocation: Uses calloc to allocate memory for the array in xs.
** - Initialization: Initializes the array with either the provided intersections or default values.
** - Count Setting: Sets the count of intersections in xs.
*/
t_intersections intersections_array(int count, t_intersection *array)
{
    t_intersections xs;
    xs.count = count;
    xs.array = calloc(count, sizeof(t_intersection));
    if (xs.array == NULL)
        return xs;

    if (array != NULL)
    {
        for (int i = 0; i < count; i++)
        xs.array[i] = array[i];
    }
    else
    {
        for (int i = 0; i < count; i++)
        xs.array[i] = intersection(0, NULL);
    }
    return xs;
}

// Calculates the intersections of a ray and a sphere
t_intersections intersect(t_sphere *s, t_ray r)
{
    t_tuple sphere_to_ray = subtract(r.origin, s->center);  // Vector from sphere center to ray origin
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s->radius * s->radius;
    float discriminant = b * b - 4 * a * c;
    //printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections result;
    result.count = 0;
    result.array = NULL;

    if (discriminant < 0) {
        //printf("No intersections\n");
        return result;
    }
    else if (discriminant == 0) {  // Tangent, one intersection
        float t = -b / (2 * a);
        t_intersection i = intersection(t, s);
        result = intersections_array(1, &i);
    }
    else
    {
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        t_intersection i1 = intersection(t1, s);
        t_intersection i2 = intersection(t2, s);
        t_intersection array[2] = {i1, i2};
        result = intersections_array(2, array);

    }
    return (result);
}

// Calculates the intersections of a ray and a sphere
t_intersections intersect_transformation(t_sphere *s, t_ray r)
{
    t_matrix *inv = inverse(s->transform);
    t_ray transfromed_ray = transform(r, inv);
    t_tuple sphere_to_ray = subtract(transfromed_ray.origin, s->center);  // Vector from sphere center to ray origin
    float a = dot(transfromed_ray.direction, transfromed_ray.direction);
    float b = 2 * dot(transfromed_ray.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s->radius * s->radius;
    float discriminant = b * b - 4 * a * c;
    //printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections result;
    result = intersections_array(0, NULL);

    if (discriminant < 0) {
        //printf("No intersections\n");
        return result;
    }
    else if (discriminant == 0) {  // Tangent, one intersection
        float t = -b / (2 * a);
        t_intersection i = intersection(t, s);
        result = intersections_array(1, &i);
    }
    else
    {
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        t_intersection i1 = intersection(t1, s);
        t_intersection i2 = intersection(t2, s);
        t_intersection array[2] = {i1, i2};
        result = intersections_array(2, array);

    }
    return (result);
}


/* HIT 
** Loop through all intersections and return the intersection with the lowest positive t value
** If there are no positive t values, return NULL
*/
t_intersection *hit(t_intersections *intersections)
{
    t_intersection *hit = NULL;
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
    return hit;
}

void set_transform(t_sphere *s, t_matrix *m)
{
    s->transform = m;
}

/* NORMAL AT
** Calculate the normal vector on a sphere at a given point
** The normal vector is the vector from the center of the sphere to the point
** Normalize the vector to get a unit vector
*/
t_tuple normal_at(t_sphere *s, t_tuple world_point)
{
    t_tuple object_point = matrix_multiply_tuple(inverse(s->transform), world_point);
    t_tuple object_normal = subtract(object_point, s->center);
    t_tuple world_normal = matrix_multiply_tuple(transpose_matrix(inverse(s->transform)), object_normal);
    world_normal.w = 0;
    return (normalize(world_normal));
}
