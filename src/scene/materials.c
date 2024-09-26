#include "structs.h"

t_color	color(float r, float g, float b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}


// A default material
t_material *material()
{
	t_material *m;

	m = calloc(1, sizeof(t_material));
	if (!m)
		return (NULL);
	m->color = color(1, 1, 1);
	m->ambient_ratio = 0.1;
	m->ambient_color = color(1, 1, 1);
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200.0;
	return (m);
}
