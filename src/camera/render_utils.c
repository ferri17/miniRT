/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:14:13 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/31 18:35:55 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	sum_lights_color(t_scene *scene, t_light *lights, t_hit *hit_rec,
		const t_ray *r)
{
	t_ray	r_light;
	t_color	diffuse_light;
	t_color	specular_light;
	t_color	pxl_color;

	pxl_color = (t_color){0, 0, 0};
	calc_shadow_ray(&r_light, lights, hit_rec);
	if (calc_hard_shadows(scene->objs, &r_light, hit_rec) == false)
	{
		diffuse_light = calc_diffuse_light(lights, &r_light, hit_rec);
		specular_light = calc_specular_light(lights, r, &r_light, hit_rec);
		pxl_color = add_vec3(&pxl_color, &diffuse_light);
		pxl_color = add_vec3(&pxl_color, &specular_light);
	}
	return (pxl_color);
}

void	apply_normal_map(t_hit *hit)
{
	t_color	n;
	t_vec3	tng;
	t_vec3	bitng;
	t_vec3	n_world;

	if (hit->obj->materia.texture == BUMPMAP
		|| hit->obj->materia.texture == BITMAP_BUMPMAP)
	{
		n = hit->obj->get_color(&hit->p, hit->obj, hit->obj->materia.bump);
		n.x = (n.x * 2) - 1;
		n.y = (n.y * 2) - 1;
		n.z = (n.z * 2) - 1;
		n = unit_vector(&n);
		tng = (t_vec3){1.0, 0.0, 0.0};
		if (fabs(dot(&hit->normal, &tng)) > 0.95)
			tng = (t_vec3){0.0, 1.0, 0.0};
		tng = cross(&tng, &hit->normal);
		tng = unit_vector(&tng);
		bitng = cross(&hit->normal, &tng);
		bitng = unit_vector(&bitng);
		n_world.x = tng.x * n.x + bitng.x * n.y + hit->normal.x * n.z;
		n_world.y = tng.y * n.x + bitng.y * n.y + hit->normal.y * n.z;
		n_world.z = tng.z * n.x + bitng.z * n.y + hit->normal.z * n.z;
		hit->normal = unit_vector(&n_world);
	}
}
