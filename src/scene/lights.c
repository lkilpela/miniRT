/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:08:02 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/03 10:47:11 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// A point light source has a position and an intensity
t_light	point_light(t_tuple position, t_color intensity)
{
	t_light	l;

	l.position = position;
	l.intensity = intensity;
    l.brightness = 1;
    l.flag = false;
	return (l);
}

t_color ambient_effect(t_world *w)
{
    return (multiply_color_by_scalar(w->ambient.color, w->ambient.ratio));
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
t_color lighting_shadow(t_world *w, t_material *material, t_tuple over_point, t_tuple eyev, t_tuple normalv, bool in_shadow)
{

    t_color diffuse;
    t_color specular;
    t_color adjusted_intensity = multiply_color_by_scalar(w->light.intensity, w->light.brightness); // Adjust the intensity of the light source 
    t_color effective_color = multiply_color(material->color, adjusted_intensity); // Combine the surface color with the light's color
    t_tuple lightv = normalize(subtract(w->light.position, over_point)); // Find the direction to the light source
    t_color ambient = multiply_color(effective_color, ambient_effect(w)); // Compute the ambient contribution
    // Light_dot_normal represents the cosine of the angle between the light vector and the normal vector. 
    // A negative number means the light is on the other side of the surface
    float light_dot_normal = dot(lightv, normalv);

    if (in_shadow || light_dot_normal < 0)
    {
        return (ambient);
    }
    diffuse = multiply_color_by_scalar(effective_color, material->diffuse * light_dot_normal); // Compute the diffuse contribution
    // reflect_dot_eye represents the cosine of the angle between the reflection vector and the eye vector.
    // A negative number means the light reflects away from the eye
    t_tuple reflectv = reflect(negate(lightv), normalv);
    float reflect_dot_eye = dot(reflectv, eyev);
    if (reflect_dot_eye <= 0)
        specular = color(0, 0, 0);
    else
    {
        float factor = pow(reflect_dot_eye, material->shininess); // Compute the specular contribution
        specular = multiply_color_by_scalar(adjusted_intensity, material->specular * factor);
    }
        
    t_color final_color = add_color(add_color(ambient, diffuse), specular);
    if (final_color. r > 1.0) // Clamp the final color to 1.0 if it exceeds it
        final_color.r = 1.0;
    if (final_color.g > 1.0)
        final_color.g = 1.0;
    if (final_color.b > 1.0)
        final_color.b = 1.0;
    return (final_color);
}

