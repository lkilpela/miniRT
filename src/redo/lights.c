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

/* PHONG REFLECTION MODEL
** AMBIENT: Background light or light reflected from other objects in the environment, coloring all points on the surface equally
** DIFFUSE: 
**  - light reflected from a matte surface.
**  - Depends on the angle between the light source and the surface normal
** SPECULAR:
**  - reflection of light source itself
**  - gives bright spot on curved surface
**  - Depends on the angle between reflecton vecgor and eye vector
**  - is controlled by the shininess parameter: the higher the value, the smaller and brighter the spot
** LIGHTING FUNCTION:
** - Five arguments: material itself, point being illuminated, light source, eye and normal vectors from PHONG REFLECTION MODEL
*/
t_color lighting(t_material *m, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    //printf("Light intensity: %f %f %f\n", light->intensity.r, light->intensity.g, light->intensity.b);
    t_color effective_color = multiply_color(m->color, light->intensity); // Combine the surface color with the light's color
    //printf("EFFECTIVE COLOR: %f %f %f\n", effective_color.r, effective_color.g, effective_color.b);
    t_tuple lightv = normalize(subtract(light->position, point)); // Find the direction to the light source
    //printf("light->position: %f %f %f\n", light->position.x, light->position.y, light->position.z);
    //printf("point: %f %f %f\n", point.x, point.y, point.z);
    t_color ambient = multiply_color_by_scalar(effective_color, m->ambient); // Compute the ambient contribution
    // Light_dot_normal represents the cosine of the angle between the light vector and the normal vector. 
    // A negative number means the light is on the other side of the surface
    float light_dot_normal = dot(lightv, normalv);

    /*    // Handle back-facing normals
    if (light_dot_normal < 0) {
        normalv = negate(normalv);
        light_dot_normal = dot(lightv, normalv);
    }*/

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
    //float reflect_dot_eye = 0.0;
    t_color final_color = add_color(add_color(ambient, diffuse), specular);
    if (final_color. r > 1.0) // Clamp the final color to 1.0 if it exceeds it
        final_color.r = 1.0;
    if (final_color.g > 1.0)
        final_color.g = 1.0;
    if (final_color.b > 1.0)
        final_color.b = 1.0;
    //printf("Final Color: ");
    //print_color(final_color);
    //printf("Light Direction: %f %f %f\n", lightv.x, lightv.y, lightv.z);
    //printf("Normal: %f %f %f\n", normalv.x, normalv.y, normalv.z);
    //printf("Light Dot Normal: %f\n", light_dot_normal);
    //printf("Reflect Dot Eye: %f\n", reflect_dot_eye);
    //printf("Ambient: %f %f %f\n", ambient.r, ambient.g, ambient.b);
    //printf("Diffuse: %f %f %f\n", diffuse.r, diffuse.g, diffuse.b);
    //printf("Specular: %f %f %f\n", specular.r, specular.g, specular.b);
    //printf("Final Color: %f %f %f\n", final_color.r, final_color.g, final_color.b);
    //printf("LIGHT(Lighting posotion): %f %f %f\n", light->position.x, light->position.y, light->position.z);
    return (final_color);
}