#include "shapes.h"

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

/**
 * @brief Calculates the intersections of a ray and a cylinder
 * 
 * @param shape 
 * @param r 
 * @return t_intersections 
 */
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
        intersect_caps(shape, r, result);
        return result;
    }

    float b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
    float c1 = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
    float discriminant = b * b - 4 * a * c1;

    if (discriminant < 0)
    {
        // Ray does not intersect the cylinder
        intersect_caps(shape, r, result);
        return result;
    }

    float t0 = (-b - sqrt(discriminant)) / (2 * a);
    float t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1)
		ft_swap(&t0, &t1);

    float y0 = r.origin.y + t0 * r.direction.y;
    if (cy->minimum < y0 && y0 < cy->maximum)
    {
        t_intersection i0 = intersection(t0, shape);
        result = intersections_array(1, &i0);
    }

    float y1 = r.origin.y + t1 * r.direction.y;
    if (cy->minimum < y1 && y1 < cy->maximum)
    {
        t_intersection i1 = intersection(t1, shape);
        result = intersections_array(1, &i1);
    }

    intersect_caps(shape, r, result);
    return result;
}

void free_intersections(t_intersections *intersections)
{
    free(intersections->array);
}

void intersect_caps(t_shape *shape, t_ray r, t_intersections result)
{
    t_cylinder *cy = SHAPE_AS_CYLINDER(shape);

    if (!cy->closed || fabs(r.direction.y) < EPSILON)
        return;

    float t = (cy->minimum - r.origin.y) / r.direction.y;
    if (check_cap(r, t))
    {
        t_intersection i = intersection(t, shape);
        result = intersections_array(1, &i);
    }

    t = (cy->maximum - r.origin.y) / r.direction.y;
    if (check_cap(r, t))
    {
        t_intersection i = intersection(t, shape);
        t_intersections xs = intersections_array(1, &i);
        add_intersections(result, xs);
        free_intersections(&xs);
    }
}
/**
 * @brief A helper function to reduce duplication. 
 * checks to see if the intersection at `t` is within a radius
 * of 1 (the radius of your cylinders) from the y axis.
 * 
 * @param r 
 * @param t 
 * @return true or false
 */
bool	check_cap(t_ray r, float t)
{
	float x;
	float z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (x * x + z * z <= 1);
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
