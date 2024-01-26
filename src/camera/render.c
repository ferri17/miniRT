/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/26 13:58:25 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

static void	draw_selection_mask(const t_ray *r, t_scene *scene, t_world *objs,
		int index)
{
	t_hit	hit_rec;

	hit_rec.ray_tmin = BIAS;
	hit_rec.ray_tmax = INT_MAX;
	if (objs == scene->selected)
	{
		if (objs->hit(r, objs->type, &hit_rec))
			scene->select_mask[index] = WHITE;
		else
			scene->select_mask[index] = BLACK;
	}
}

t_color	send_ray(const t_ray *r, t_scene *scene, int i, int j)
{
	t_hit	hit_rec;
	t_world	*objs;

	hit_rec.obj = NULL;
	hit_rec.ray_tmin = BIAS;
	hit_rec.ray_tmax = INT_MAX;
	objs = scene->objs;
	while (objs)
	{
		draw_selection_mask(r, scene, objs, i + (j * IMG_W));
		if (objs->hit(r, objs->type, &hit_rec))
		{
			hit_rec.ray_tmax = hit_rec.t;
			hit_rec.obj = objs;
		}
		objs = objs->next;
	}
	if (hit_rec.obj)
	{
		if (scene->render_mode == EDIT_MODE)
			return (render_edit_mode(scene, r, &hit_rec));
		else
			return (render_raytrace_mode(scene, r, &hit_rec, RAY_DEPTH));
	}
	return (scene->bg_color);
}

t_color	render_edit_mode(t_scene *scene, const t_ray *r, t_hit *hit_rec)
{
	t_color	color;
	t_vec3	view_dir;
	double	a;

	view_dir = product_vec3_r(&r->dir, -1);
	view_dir = unit_vector(&view_dir);
	a = dot(&view_dir, &hit_rec->normal) - 0.5;
	color = hit_rec->obj->get_color(&hit_rec->p, hit_rec->obj);
	color = product_vec3_r(&color, 0.5);
	color = (t_color){color.x + a, color.y + a, color.z + a};
	/* if (hit_rec->obj == scene->selected)
		color = (t_color){hit_rec->normal.x, hit_rec->normal.y,
			hit_rec->normal.z}; */
	(void)scene;
	return (color);
}

void	calc_shadow_ray(t_ray *shadow_ray, t_light *lights, t_hit *hit_rec)
{
	shadow_ray->orig = product_vec3_r(&hit_rec->normal, BIAS);
	shadow_ray->orig = add_vec3(&hit_rec->p, &shadow_ray->orig);
	shadow_ray->dir = substract_vec3(&lights->center, &shadow_ray->orig);
	shadow_ray->len_sqrd = length_squared(&shadow_ray->dir);
	shadow_ray->dir = unit_vector(&shadow_ray->dir);
}

t_color	render_raytrace_mode(t_scene *scene, const t_ray *r, t_hit *hit_rec, int ray_depth)
{
	t_color	pxl_color;
	t_color	diffuse_light;
	t_color	specular_light;
	t_color	reflect;
	t_ray	r_light;
	t_light	*lights;

	if (ray_depth <= 0)
		return ((t_color){0, 0, 0});
	if (hit_rec->obj->materia.texture == BUMPMAP || hit_rec->obj->materia.texture == BITMAP_BUMPMAP)
	{
		t_color	normal_d = hit_rec->obj->get_normal_map(&hit_rec->p, hit_rec->obj);
		normal_d = unit_vector(&normal_d);
		hit_rec->normal = normal_d;
		/* normal_d.x = (normal_d.x * 2) - 1;
		normal_d.y = (normal_d.y * 2) - 1;
		normal_d.z = (normal_d.z * 2) - 1; */
	}
	pxl_color = hit_rec->obj->get_color(&hit_rec->p, hit_rec->obj);
	pxl_color = calc_ambient_light(&scene->amblight.color, &pxl_color,
			scene->amblight.ratio);
	//return (pxl_color);
	lights = scene->light;
	while (lights)
	{
		calc_shadow_ray(&r_light, lights, hit_rec);
		if (calc_hard_shadows(scene->objs, &r_light, hit_rec) == false)
		{
			diffuse_light = calc_diffuse_light(lights, &r_light, hit_rec);
			specular_light = calc_specular_light(lights, r, &r_light, hit_rec);
			pxl_color = add_vec3(&pxl_color, &diffuse_light);
			pxl_color = add_vec3(&pxl_color, &specular_light);
		}
		lights = lights->next;
	}
	product_vec3(&pxl_color, 1 - hit_rec->obj->materia.metallic);
	reflect = calc_reflected_color(scene, hit_rec, r, ray_depth);
	pxl_color = add_vec3(&pxl_color, &reflect);
	return (pxl_color);
}
