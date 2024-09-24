#include "structs.h"

t_computations prepare_computations(t_intersection i, t_ray r)
{
    t_computations comps;

    // Copy the intersection's properties, for convenience
    comps.t = i.t;
    comps.shape = i.object;

    // Precompute some useful values
    comps.point = position(r, comps.t);
    comps.eyev = negate(r.direction);
    comps.normalv = normal_at_shape(comps.shape, comps.point);
    

    // If the dot product is negative, the normal points inwards
    if (dot(comps.normalv, comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = negate(comps.normalv);
    } else {
        comps.inside = false;
    }

    // Compute over_point to avoid shadow acne
    // EPSILON is a small number, 1e-6. Is used here to bump the point just a bit in the direction of the normal.
    comps.over_point = add(comps.point, multiply_by_epsilon(comps.normalv));
/*     printf(RED "over_point: " RESET);
    print_tuple(comps.over_point); */

    return comps;
}
