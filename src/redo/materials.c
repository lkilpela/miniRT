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


/*void test_lighting()
{
    t_material m = material();
    t_light l;
    l.position = point(0, 0, 0);

    // Lighting with the eye between the light and the surface
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1);
    t_light light = point_light(point(0, 0, -10), color(1, 1, 1));


}*/