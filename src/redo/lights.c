#include "structs.h"

// A point light source has a position and an intensity
t_light light(t_tuple position, t_color intensity)
{
    t_light l;

    l.position = position;
    l.intensity = intensity;
    return (l);
}

