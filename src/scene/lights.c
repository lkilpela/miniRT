/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:08:02 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/03 14:26:38 by lkilpela         ###   ########.fr       */
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

// Clamp the color to prevent the color from exceeding the maximum value of 1.0
void	clamp_color(t_color *c)
{
	if (c->r > 1.0)
		c->r = 1.0;
	if (c->g > 1.0)
		c->g = 1.0;
	if (c->b > 1.0)
		c->b = 1.0;
}

// Compute the ambient contribution to the lighting
t_color	compute_ambient(t_color effective_color, t_world *w)
{
	t_color intensity;
	t_color ambient_effect;

	intensity = multiply_color_by_scalar(w->ambient.color, w->ambient.ratio);
	ambient_effect = multiply_color(intensity, effective_color);
	return (ambient_effect);
}

// Compute the diffuse contribution to the lighting
t_color	compute_diffuse(t_color effective_color, t_material *material,
					float light_dot_normal)
{
	return (multiply_color_by_scalar(effective_color,
								material->diffuse * light_dot_normal));
}

// Compute the specular contribution to the lighting
// reflect_dot_eye represents the cosine of the angle between the reflection
// vector and the eye vector.
// A negative number means the light reflects away from the eye
t_color	compute_specular(t_tuple lightv, t_computations comps, 
					t_material *material, t_color adjusted_intensity)
{
	t_tuple	reflectv;
	float	reflect_dot_eye;
	float	factor;
	
	reflectv = reflect(negate(lightv), comps.normalv);
	reflect_dot_eye  = dot(reflectv, comps.eyev);
	if (reflect_dot_eye <= 0)
		return color(0, 0, 0);
	factor = pow(reflect_dot_eye, material->shininess);
	return (multiply_color_by_scalar(adjusted_intensity,
		material->specular * factor));
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
t_color	lighting(t_world *w, t_computations comps, t_material *material, bool in_shadow)
{
	t_color ambient;
	t_color diffuse;
	t_color specular;
	t_color adjusted_intensity;
	t_color effective_color;
	t_tuple lightv;
	float light_dot_normal;
	t_color final_color;

	adjusted_intensity = multiply_color_by_scalar(w->light.intensity, w->light.brightness); // Adjust the intensity of the light source 
	effective_color = multiply_color(material->color, adjusted_intensity); // Combine the surface color with the light's color
	lightv = normalize(subtract(w->light.position, comps.over_point)); // Find the direction to the light source
	ambient = compute_ambient(effective_color, w);
	// Light_dot_normal represents the cosine of the angle between the light vector and the normal vector. 
	// A negative number means the light is on the other side of the surface
	light_dot_normal = dot(lightv, comps.normalv);
	if (in_shadow || light_dot_normal < 0)
		return (ambient);
	diffuse = compute_diffuse(effective_color, material, light_dot_normal);
	specular = compute_specular(lightv, comps, material, adjusted_intensity);
	final_color = add_color(add_color(ambient, diffuse), specular);
	clamp_color(&final_color);
    return (final_color);
}

