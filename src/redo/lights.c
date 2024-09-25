/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:08:02 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/25 14:11:24 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// A point light source has a position and an intensity
t_light	point_light(t_tuple position, t_color intensity)
{
	t_light	l;

	l.position = position;
	l.intensity = intensity;
	return (l);
}

t_color lighting_shadow(t_material *m, t_light *light, t_tuple over_point, t_tuple eyev, t_tuple normalv, bool in_shadow)
{
    t_color effective_color = multiply_color(m->color, light->intensity); // Combine the surface color with the light's color
    t_tuple lightv = normalize(subtract(light->position, over_point)); // Find the direction to the light source
    t_color ambient = multiply_color_by_scalar(effective_color, m->ambient); // Compute the ambient contribution
    // Light_dot_normal represents the cosine of the angle between the light vector and the normal vector. 
    // A negative number means the light is on the other side of the surface
    float light_dot_normal = dot(lightv, normalv);

    // Handle back-facing normals
    if (light_dot_normal < 0) {
        normalv = negate(normalv);
        light_dot_normal = dot(lightv, normalv);
    }

    if (in_shadow)
    {
        return (ambient);
    }

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
    t_color final_color = add_color(add_color(ambient, diffuse), specular);
    if (final_color. r > 1.0) // Clamp the final color to 1.0 if it exceeds it
        final_color.r = 1.0;
    if (final_color.g > 1.0)
        final_color.g = 1.0;
    if (final_color.b > 1.0)
        final_color.b = 1.0;
    return (final_color);
}

