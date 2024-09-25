#include "structs.h"

#define SHAPE_AS_CYLINDER(shape) ((t_cylinder *)(shape)->object)

t_shape	*cylinder()
{
	t_shape		*object;
	t_cylinder	*cy;

	object = shape();
	cy = calloc(1, sizeof(t_cylinder));
	object->local_intersect = local_intersect_cylinder;
	object->local_normal_at = local_normal_at_cylinder;
	cy->minimum = -INFINITY;
	cy->maximum = INFINITY;
	cy->closed = false;
	return (object);
}

t_intersections local_intersect_cylinder(t_shape *shape, t_ray r)
{
    t_cylinder *cy = SHAPE_AS_CYLINDER(shape);

    t_intersections result;
    result.count = 0;
    result.array = NULL;

    float a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;

    if (a < EPSILON && a > -EPSILON)
    {
        // Ray is parallel to the y-axis
        intersect_caps(cy, r, &result);
        return result;
    }

    float b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
    float c1 = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
    float discriminant = b * b - 4 * a * c1;

    if (discriminant < 0)
    {
        // Ray does not intersect the cylinder
        intersect_caps(cy, r, &result);
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
    if (cy->minimum < y0 && y0 < cy->maximum)
    {
        t_intersection i0 = intersection(t0, cy);
        result = intersections_array(1, &i0);
    }

    float y1 = r.origin.y + t1 * r.direction.y;
    if (cy->minimum < y1 && y1 < cy->maximum)
    {
        t_intersection i1 = intersection(t1, cy);
        result = intersections_array(1, &i1);
    }

    intersect_caps(cy, r, &result);
    return result;
}


void intersect_caps(t_cylinder *cy, t_ray r, t_intersections *result)
{
    if (!cy->closed || fabs(r.direction.y) < EPSILON)
        return;

    float t = (cy->minimum - r.origin.y) / r.direction.y;
    if (check_cap(r, t))
    {
        t_intersection i = intersection(t, cy);
        *result = intersections_array(1, &i);
    }

    t = (cy->maximum - r.origin.y) / r.direction.y;
    if (check_cap(r, t))
    {
        t_intersection i = intersection(t, cy);
        t_intersections xs = intersections_array(1, &i);
        append_intersections(result, xs);
        free_intersections(&xs);
    }
}

bool check_cap(t_ray r, float t)
{
    float x = r.origin.x + t * r.direction.x;
    float z = r.origin.z + t * r.direction.z;
    return x * x + z * z <= 1;
}

t_tuple local_normal_at_cylinder(t_shape *shape, t_tuple point)
{
    t_cylinder *c = SHAPE_AS_CYLINDER(shape);

    float dist = point.x * point.x + point.z * point.z;

    if (dist < 1 && point.y >= c->maximum - EPSILON)
        return vector(0, 1, 0);
    else if (dist < 1 && point.y <= c->minimum + EPSILON)
        return vector(0, -1, 0);
    else
        return vector(point.x, 0, point.z);
}

void set_minimum(t_cylinder *c, float min)
{
    c->minimum = min;
}

void set_maximum(t_cylinder *c, float max)
{
    c->maximum = max;
}

void set_closed(t_cylinder *c, bool closed)
{
    c->closed = closed;
}

void test_cylinder()
{
    // Ray misses a cylinder
    t_shape *cy = cylinder();
    t_ray r = ray(point(1, 0, 0), vector(0, 1, 0));
    t_intersections xs = local_intersect_cylinder(cy, r);
    assert(xs.count == 0);
    free_intersections(&xs);
    printf("PASSED: Ray misses a cylinder\n");

    // Ray strikes a cylinder
    r = ray(point(1, 0, -5), vector(0, 0, 1));
    xs = local_intersect_cylinder(cy, r);
    assert(xs.count == 2);
    assert(xs.array[0].t == 5);
    assert(xs.array[1].t == 5);
    free_intersections(&xs);
    printf("PASSED: Ray strikes a cylinder\n");

    // Ray misses a capped cylinder
    cy.closed = true;
    r = ray(point(0, 0, -5), vector(0, 1, 0));
    xs = local_intersect_cylinder(cy, r);
    assert(xs.count == 0);
    free_intersections(&xs);
    printf("PASSED: Ray misses a capped cylinder\n");

    // Ray strikes the caps of a closed cylinder
    r = ray(point(0, 0, -5), vector(0, 0, 1));
    xs = local_intersect_cylinder(cy, r);
    assert(xs.count == 2);
    assert(xs.array[0].t == 4);
    assert(xs.array[1].t == 6);
    free_intersections(&xs);
    printf("PASSED: Ray strikes the caps of a closed cylinder\n");

    // Normal vector on a cylinder
    t_tuple n = local_normal_at_cylinder(cy, point(1, 0, 0));
    assert(tuple_equal(n, vector(1, 0, 0)));
    n = local_normal_at_cylinder(cy, point(0, 5, -1));
    assert(tuple_equal(n, vector(0, 0, -1)));
    n = local_normal_at_cylinder(cy, point(0, -2, 1));
    assert(tuple_equal(n, vector(0, 0, 1)));
    n = local_normal_at_cylinder(cy, point(-1, 1, 0));
    assert(tuple_equal(n, vector(-1, 0, 0)));
    printf("PASSED: Normal vector on a cylinder\n");
}