#include "structs.h"

#define SHAPE_AS_CONE(shape) ((t_cone *)(shape)->object)

typedef struct s_cone
{
    t_shape base;
    float minimum;
    float maximum;
    bool closed;
}              t_cone;

t_cone cone()
{
    t_cone c;

    c.base = shape();
    c.base.local_intersect = local_intersect_cone;
    c.base.local_normal_at = local_normal_at_cone;
    c.minimum = -INFINITY;
    c.maximum = INFINITY;
    c.closed = false;
    return c;
}

t_intersections local_intersect_cone(t_shape *shape, t_ray r)
{
    t_cone *c = SHAPE_AS_CONE(shape);

    t_intersections result;
    result.count = 0;
    result.array = NULL;

    float a = r.direction.x * r.direction.x - r.direction.y * r.direction.y + r.direction.z * r.direction.z;

    float b = 2 * r.origin.x * r.direction.x - 2 * r.origin.y * r.direction.y + 2 * r.origin.z * r.direction.z;

    float c1 = r.origin.x * r.origin.x - r.origin.y * r.origin.y + r.origin.z * r.origin.z;

    if (fabs(a) < EPSILON && fabs(b) < EPSILON)
    {
        // Ray is parallel to the y-axis
        intersect_caps(c, r, &result);
        return result;
    }

    float discriminant = b * b - 4 * a * c1;

    if (discriminant < 0)
    {
        // Ray does not intersect the cone
        intersect_caps(c, r, &result);
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

    float y0 = r.origin.y + t0 * r.direction.y;
    if (c->minimum < y0 && y0 < c->maximum)
    {
        t_intersection i = intersection(t0, c);
        result = intersections_array(1, &i);
    }

    float y1 = r.origin.y + t1 * r.direction.y;
    if (c->minimum < y1 && y1 < c->maximum)
    {
        t_intersection i = intersection(t1, c);
        result = intersections_array(1, &i);
    }

    intersect_caps(c, r, &result);

    return result;
}

void intersect_caps(t_cone *c, t_ray r, t_intersections *result)
{
    if (!c->closed || fabs(r.direction.y) < EPSILON)
        return;

    float t = (c->minimum - r.origin.y) / r.direction.y;
    if (check_cap(r, t, c->minimum))
    {
        t_intersection i = intersection(t, c);
        *result = intersections_array(1, &i);
    }

    t = (c->maximum - r.origin.y) / r.direction.y;
    if (check_cap(r, t, c->maximum))
    {
        t_intersection i = intersection(t, c);
        t_intersections xs = intersections_array(1, &i);
        append_intersections(result, xs);
        free_intersections(&xs);
    }
}

bool check_cap(t_ray r, float t, float radius)
{
    float x = r.origin.x + t * r.direction.x;
    float z = r.origin.z + t * r.direction.z;

    return (x * x + z * z) <= fabs(radius);
}

t_tuple local_normal_at_cone(t_shape *shape, t_tuple point)
{
    t_cone *c = SHAjsonPE_AS_CONE(shape);

    float dist = point.x * point.x + point.z * point.z;

    if (dist < 1 && point.y >= c->maximum - EPSILON)
        return vector(0, 1, 0);
    else if (dist < 1 && point.y <= c->minimum + EPSILON)
        return vector(0, -1, 0);

    float y = sqrt(dist);
    if (point.y > 0)
        y = -y;

    return vector(point.x, y, point.z);
}

void set_minimum(t_cone *c, float min)
{
    c->minimum = min;
}

void set_maximum(t_cone *c, float max)
{
    c->maximum = max;
}

void set_closed(t_cone *c, bool closed)
{
    c->closed = closed;
}

void set_transform_cone(t_cone *c, t_matrix *m)
{
    set_transform_shape(&c->base, m);
}

void test_cone()
{
    // Intersecting a cone with a ray
    t_cone c = cone();
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_intersections xs = local_intersect_cone(&c.base, r);
    assert(xs.count == 2);
    assert(xs.array[0].t == 5);
    assert(xs.array[1].t == 5);
    free_intersections(&xs);
    printf("PASSED: Intersecting a cone with a ray\n");

    // Intersecting a cone with a ray parallel to one of its halves
    r = ray(point(0, 0, -5), vector(0, 1, 1));
    xs = local_intersect_cone(&c.base, r);
    assert(xs.count == 1);
    assert(xs.array[0].t == 8.66025);
    free_intersections(&xs);
    printf("PASSED: Intersecting a cone with a ray parallel to one of its halves\n");

    // Intersecting a cone's end caps
    c.minimum = -0.5;
    c.maximum = 0.5;
    c.closed = true;
    r = ray(point(0, 0, -5), vector(0, 1, 0));
    xs = local_intersect_cone(&c.base, r);
    assert(xs.count == 2);
    free_intersections(&xs);
    printf("PASSED: Intersecting a cone's end caps\n");
}
