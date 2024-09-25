#include "shapes.h"

t_shape	*sphere()
{
	t_shape		*object;
	t_sphere	*sp;

	object = shape();
	object = calloc(1, sizeof(t_sphere));
	object->object = sp;
	object->local_intersect = local_intersect_sphere;
	object->local_normal_at = local_normal_at_sphere;
	sp->center = point(0, 0, 0);
	sp->radius = 1;
	sp->color = color(1, 1, 1);
	return (object);
}

/* t_shape *sphere_2(t_sphere* sp)
{
    t_shape *sh = shape();

    sh->object = sp;
    sh->local_intersect = local_intersect_sphere;
    sh->local_normal_at = local_normal_at_sphere;
    sp->center = point(0, 0, 0);
    sp->radius = 1;    
    return (sh);
} */

#define SPHERE 1

void set_sphere_params(t_shape *shape, t_tuple center, float radius)
{
    if(shape->id == SPHERE) {
        t_sphere *sp = SHAPE_AS_SPHERE(shape);
        sp->center = center;
        sp->radius = radius;
    }
}

t_sphere *cast_to_sphere(t_shape *shape)
{
    if(shape->id == SPHERE)
        return SHAPE_AS_SPHERE(shape);
    return NULL;
}

// Calculates the intersections of a ray and a sphere
t_intersections	local_intersect_sphere(t_shape *shape, t_ray r)
{
	t_sphere	*sp;

	sp = SHAPE_AS_SPHERE(shape);

	t_tuple sphere_to_ray = subtract(r.origin, sp->center);  // Vector from sphere center to ray origin
	float a = dot(r.direction, r.direction);
	float b = 2 * dot(r.direction, sphere_to_ray);
	float c = dot(sphere_to_ray, sphere_to_ray) - sp->radius * sp->radius;
	float discriminant = b * b - 4 * a * c;

	t_intersections result;
	result.count = 0;
	result.array = NULL;

	if (discriminant < 0)
		return result;
	else if (discriminant == 0)
	{
		float t = -b / (2 * a);
		t_intersection i = intersection(t, shape);
		result = intersections_array(1, &i);
	}
	else
	{
		float t1 = (-b - sqrt(discriminant)) / (2 * a);
		float t2 = (-b + sqrt(discriminant)) / (2 * a);
		t_intersection i1 = intersection(t1, shape);
		t_intersection i2 = intersection(t2, shape);
		t_intersection array[2] = {i1, i2};
		result = intersections_array(2, array);

	}
	return (result);
}

/**
 * @brief Calculates the normal at a given point on a sphere in local space.
 * 
 * @param shape The shape to calculate the normal for.
 * @param point The point at which to calculate the normal.
 * @return The normal vector at the given point.
 */
t_tuple	local_normal_at_sphere(t_shape *shape, t_tuple point)
{
	t_sphere	*sp;
	t_tuple		normal;

	sp = SHAPE_AS_SPHERE(shape);	
	normal = subtract(point, sp->center);
	return (normal);
}
