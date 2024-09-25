#include "structs.h"

#define SHAPE_AS_HYPERBOLOID(shape) ((t_hyperboloid *)(shape)->object)

typedef struct s_hyperboloid
{
    t_shape base;
    float a;
    float b;
    float c;
}              t_hyperboloid;

t_hyperboloid hyperboloid()
{
    t_hyperboloid h;

    h.base = shape();
    h.base.local_intersect = local_intersect_hyperboloid;
    h.base.local_normal_at = local_normal_at_hyperboloid;
    h.a = 1;
    h.b = 1;
    h.c = 1;
    return h;
}

t_intersections local_intersect_hyperboloid(t_shape *shape, t_ray r)
{
    t_hyperboloid *h = SHAPE_AS_HYPERBOLOID(shape);

    t_intersections result;
    result.count = 0;
    result.array = NULL;

    float a = r.direction.x * r.direction.x / (h->a * h->a) - r.direction.y * r.direction.y / (h->b * h->b) + r.direction.z * r.direction.z / (h->c * h->c);

    float b = 2 * r.origin.x * r.direction.x / (h->a * h->a) - 2 * r.origin.y * r.direction.y / (h->b * h->b) + 2 * r.origin.z * r.direction.z / (h->c * h->c);

    float c1 = r.origin.x * r.origin.x / (h->a * h->a) - r.origin.y * r.origin.y / (h->b * h->b) + r.origin.z * r.origin.z / (h->c * h->c);

    if (fabs(a) < EPSILON && fabs(b) < EPSILON)
    {
        // Ray is parallel to the y-axis
        return result;
    }

    float discriminant = b * b - 4 * a * c1;

    if (discriminant < 0)
    {
        // Ray does not intersect the hyperboloid
        return result;
    }

    float t0 = (-b - sqrt(discriminant)) / (2 * a);
    float t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1)
    {
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    t_intersection i1 = intersection(t0, h);
    t_intersection i2 = intersection(t1, h);
    t_intersection array[2] = {i1, i2};
    result = intersections_array(2, array);

    return result;
}

t_tuple local_normal_at_hyperboloid(t_shape *shape, t_tuple object_point)
{
    t_hyperboloid *h = SHAPE_AS_HYPERBOLOID(shape);

    float a2 = object_point.x * object_point.x / (h->a * h->a);
    float b2 = object_point.y * object_point.y / (h->b * h->b);
    float c2 = object_point.z * object_point.z / (h->c * h->c);

    float normal_x = 2 * a2;
    float normal_y = -2 * b2;
    float normal_z = 2 * c2;

    t_tuple normal = vector(normal_x, normal_y, normal_z);
    normal.w = 0;
    return normal;
}

void set_transform_shape(t_shape *shape, t_matrix *m)
{
    shape->transform = m;
}

void test_hyperboloid()
{
    // Ray intersecting a hyperboloid
    t_hyperboloid h = hyperboloid();
    t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    t_intersections xs = local_intersect_hyperboloid(&h.base, r);
    assert(xs.count == 2);
    assert(xs.array[0].t == -1);
    assert(xs.array[1].t == 1);
    free_intersections(&xs);
    printf("PASSED: Ray intersecting a hyperboloid\n");

    // Ray intersecting a hyperboloid from the side
    r = ray(point(0, 0, 0), vector(1, 0, 0));
    xs = local_intersect_hyperboloid(&h.base, r);
    assert(xs.count == 0);
    free_intersections(&xs);
    printf("PASSED: Ray intersecting a hyperboloid from the side\n");

    // Ray intersecting a hyperboloid from the top
    r = ray(point(0, 0, 0), vector(0, 1, 0));
    xs = local_intersect_hyperboloid(&h.base, r);
    assert(xs.count == 0);
    free_intersections(&xs);
    printf("PASSED: Ray intersecting a hyperboloid from the top\n");
}
