/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/13 12:54:39 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	send_ray(const t_ray *r, t_scene *scene)
{
	t_hit	hit_rec;
	t_world	*objs;
	t_world	*hit_obj;
	
	hit_obj = NULL;
	hit_rec.ray_tmin = 0;
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
	t_vec3 tmp1 = product_vec3_r(&r->dir, -1);
	t_vec3 tmp2 = unit_vector(&tmp1);
	double	a = dot(&tmp2, &hit_rec->normal);

	clamp_number(a, 0, 1);
	color = (t_color){a, a, a};
	if (objs == scene->selected)
		color = (t_color){hit_rec->normal.x, hit_rec->normal.y, hit_rec->normal.z};
	return (color);
}

t_color	render_raytrace_mode(t_scene *scene, const t_ray *r, t_world *hit_obj, t_hit* hit_rec)
{
	t_color pxl_color;
	t_color	ambient_light;
	t_color	diffuse_light;
	//t_color	specular_light;
	t_ray	r_light;
	//t_color	diffuse_color;
	double	len_sqrd;

	(void)r;
	(void)hit_rec;
	(void)hit_obj;

	r_light.dir = substract_vec3(&scene->light->center, &hit_rec->p);
	len_sqrd = ft_max(length_squared(&r_light.dir), 0.000001);
	r_light.dir = unit_vector(&r_light.dir);
	r_light.orig = hit_rec->p;
	
	ambient_light = calc_ambient_light(&scene->amblight.color, &hit_obj->color, scene->amblight.ratio);
	
	//if (calc_hard_shadows(scene->objs, &r_light, len_sqrd))
		//return (pxl_color);
		
	diffuse_light = calc_diffuse_light(scene, &r_light, hit_rec, len_sqrd, hit_obj);
	
	//specular_light = calc_specular_light(scene, r, &r_light, hit_rec, len_sqrd);
	
	pxl_color = add_vec3(&ambient_light, &diffuse_light);
	pxl_color = diffuse_light;
	//pxl_color = add_vec3(&pxl_color, &specular_light);
	return (pxl_color);
}

//contribution = sphereColor * dot(N, L) * lightIntensity / distanceToLight^2;
