/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/22 01:16:40 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	send_ray(const t_ray *r, t_scene *scene)
{
	t_hit	hit_rec;
	t_world	*objs;
	t_world	*hit_obj;
	
	hit_obj = NULL;
	hit_rec.ray_tmin = BIAS;
	hit_rec.ray_tmax = INT_MAX;
	objs = scene->objs;
	while (objs)
	{
		if (objs->hit(r, objs->type, &hit_rec))
		{
			hit_rec.ray_tmax = hit_rec.t;
			hit_obj = objs;
		}
		objs = objs->next;
	}
	if (hit_obj)
	{
		if (scene->render_mode == EDIT_MODE)
			return (render_edit_mode(scene, hit_obj, r, &hit_rec));
		else
			return (render_raytrace_mode(scene, r, hit_obj, &hit_rec));
	}
	return (scene->bg_color);
}

t_color	render_edit_mode(t_scene *scene, t_world *objs, const t_ray *r, t_hit *hit_rec)
{
	t_color	color;
	t_vec3 view_dir;
	double	a;

	view_dir = product_vec3_r(&r->dir, -1);
	view_dir = unit_vector(&view_dir);
	a = dot(&view_dir, &hit_rec->normal) * 0.5;
	color = product_vec3_r(&objs->color, 0.5);
	color = (t_color){color.x + a, color.y + a, color.z + a};
	if (objs == scene->selected)
		color = (t_color){hit_rec->normal.x, hit_rec->normal.y, hit_rec->normal.z};
	return (color);
}

void	calc_shadow_ray(t_ray *shadow_ray, t_light *lights, t_hit *hit_rec)
{
	shadow_ray->orig = product_vec3_r(&hit_rec->normal, BIAS);
	shadow_ray->orig = add_vec3(&hit_rec->p, &shadow_ray->orig);
	shadow_ray->dir = substract_vec3(&lights->center, &hit_rec->p);
	shadow_ray->len_sqrd = length_squared(&shadow_ray->dir);
	shadow_ray->dir = unit_vector(&shadow_ray->dir);
}

t_color	render_raytrace_mode(t_scene *scene, const t_ray *r, t_world *hit_obj, t_hit* hit_rec)
{
	t_color pxl_color;
	t_color	diffuse_light;
	t_color	specular_light;
	t_ray	r_light;
	t_light	*lights;

	pxl_color = calc_ambient_light(&scene->amblight.color, &hit_obj->color, scene->amblight.ratio);
	lights = scene->light;
	while (lights)
	{
		calc_shadow_ray(&r_light, lights, hit_rec);
		if (calc_hard_shadows(scene->objs, &r_light, hit_rec) == false)
		{
			diffuse_light = calc_diffuse_light(lights, &r_light, hit_rec, hit_obj);
			specular_light = calc_specular_light(lights, r, &r_light, hit_rec);
			pxl_color = add_vec3(&pxl_color, &diffuse_light);
			pxl_color = add_vec3(&pxl_color, &specular_light);
		}
		lights = lights->next;
	}
	return (pxl_color);
}
