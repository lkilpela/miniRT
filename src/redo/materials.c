#include "structs.h"

t_color color(float r, float g, float b)
{
    t_color c;

    c.r = r;
    c.g = g;
    c.b = b;
    return (c);
}


// A default material
t_material material()
{
    t_material m;

    m.color = color(1, 1, 1);
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;
    return (m);
}

bool color_equal(t_color a, t_color b, float epsilon)
{
    return fabs(a.r - b.r) < epsilon && fabs(a.g - b.g) < epsilon && fabs(a.b - b.b) < epsilon;
}


