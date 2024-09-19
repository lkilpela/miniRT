#include "structs.h"

t_sphere create_sphere(t_tuple center, float radius, int id)
{
    t_sphere s;

    s.center = center;
    s.radius = radius;
    s.id = id;
    return (s);
}

