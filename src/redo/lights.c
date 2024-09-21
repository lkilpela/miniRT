#include "structs.h"

// A point light source has a position and an intensity
t_light point_light(t_tuple position, t_color intensity)
{
    t_light l;

    l.position = position;
    l.intensity = intensity;
    return (l);
}

t_color multiply_color(t_color c1, t_color c2)
{
    t_color result;

    result.r = c1.r * c2.r;
    result.g = c1.g * c2.g;
    result.b = c1.b * c2.b;
    return (result);
}

t_color multiply_color_by_scalar(t_color c, float scalar)
{
    t_color result;

    result.r = c.r * scalar;
    result.g = c.g * scalar;
    result.b = c.b * scalar;
    return (result);
}

t_color add_color(t_color c1, t_color c2)
{
    t_color result;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;
    return (result);
}

t_color lighting(t_material *m, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    t_color effective_color = multiply_color(m->color, light->intensity); // Combine the surface color with the light's color
    t_tuple lightv = normalize(subtract(light->position, point)); // Find the direction to the light source  
    t_color ambient = multiply_color_by_scalar(effective_color, m->ambient); // Compute the ambient contribution
    // Light_dot_normal represents the cosine of the angle between the light vector and the normal vector. 
    // A negative number means the light is on the other side of the surface
    float light_dot_normal = dot(lightv, normalv);
    t_color diffuse;
    t_color specular;

    if (light_dot_normal < 0)
    {
        diffuse = color(0, 0, 0);
        specular = color(0, 0, 0);
    }
    else
    {
        diffuse = multiply_color_by_scalar(effective_color, m->diffuse * light_dot_normal); // Compute the diffuse contribution
        // reflect_dot_eye represents the cosine of the angle between the reflection vector and the eye vector.
        // A negative number means the light reflects away from the eye
        t_tuple reflectv = reflect(negate(lightv), normalv);
        float reflect_dot_eye = dot(reflectv, eyev);
        if (reflect_dot_eye <= 0)
            specular = color(0, 0, 0);
        else
        {
            float factor = pow(reflect_dot_eye, m->shininess); // Compute the specular contribution
            specular = multiply_color_by_scalar(light->intensity, m->specular * factor);
        }
    }
    return (add_color(add_color(ambient, diffuse), specular));
}