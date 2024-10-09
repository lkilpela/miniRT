/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:08:02 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 18:31:36 by lkilpela         ###   ########.fr       */
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

/* AMBIENT: Background light or light reflected from other objects in 
** the environment, coloring all points on the surface equally
*/
static t_color	compute_ambient(t_color effective_color, t_world *w)
{
	t_color	intensity;
	t_color	ambient_effect;

	intensity = multiply_color_by_scalar(w->ambient.color, w->ambient.ratio);
	ambient_effect = multiply_color(intensity, effective_color);
	return (ambient_effect);
}

/* DIFFUSE: 
**  - light reflected from a matte surface.
**  - Depends on the angle between the light source and the surface normal
*/
static t_color	compute_diffuse(t_color effective_color, t_material *material,
					float light_dot_normal)
{
	return (multiply_color_by_scalar(effective_color,
			material->diffuse * light_dot_normal));
}

/* SPECULAR:
**  - reflection of light source itself
**  - gives bright spot on curved surface
**  - Depends on the angle between reflecton vector and eye vector
**  - is controlled by the shininess parameter: the higher the value,
**  the smaller and brighter the spot
**  - reflect_dot_eye represents the cosine of the angle between reflection
** and eye vector. A negative number means the light reflects away from eye
*/
static t_color	compute_specular(t_tuple lightv, t_computations comps,
					t_material *material, t_color adjusted_intensity)
{
	t_tuple	reflectv;
	float	reflect_dot_eye;
	float	factor;

	reflectv = reflect(negate(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	if (reflect_dot_eye <= 0)
		return (color(0, 0, 0));
	factor = pow(reflect_dot_eye, material->shininess);
	return (multiply_color_by_scalar(adjusted_intensity,
			material->specular * factor));
}

/* PHONG REFLECTION MODEL
** 1. Adjust the intensity of the light source
** 2. Combine the surface color with the light's color
** 3. Find the direction to the light source
** 4. Calculate the ambient light, diffuse light, and specular light
** 5. Light dot normal is the cosine of the angle between the light and normal
** 	- If surface is in shadow or the light is behind surface, return ambient
** 5. Combine the results to get the final color
*/
t_color	lighting(t_world *w,
			t_computations comps,
			t_material *material,
			bool in_shadow)
{
	t_light_params	params;
	t_color			adjusted_intensity;
	t_color			effective_color;
	t_color			final_color;

	adjusted_intensity = multiply_color_by_scalar(w->light.intensity,
			w->light.brightness);
	effective_color = multiply_color(material->color, adjusted_intensity);
	params.lightv = normalize(subtract(w->light.position, comps.over_point));
	params.ambient = compute_ambient(effective_color, w);
	params.light_dot_normal = dot(params.lightv, comps.normalv);
	if (in_shadow || params.light_dot_normal < 0)
		return (params.ambient);
	params.diffuse = compute_diffuse(effective_color, material,
			params.light_dot_normal);
	params.specular = compute_specular(params.lightv, comps, material,
			adjusted_intensity);
	final_color = add_color(add_color(params.ambient, params.diffuse),
			params.specular);
	clamp_color(&final_color);
	return (final_color);
}
