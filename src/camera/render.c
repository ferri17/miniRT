/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/07 17:48:45 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	render_edit_mode(t_scene *scene, t_world *objs, const t_ray *r, t_hit *hit)
{
	t_color	color;
	t_vec3 tmp1 = product_vec3_r(&r->dir, -1);
	t_vec3 tmp2 = unit_vector(&tmp1);
	double	a = dot(&tmp2, &hit->normal);
	clamp_number(a, 0, 1);
	color = (t_color){a, a, a};
	if (objs == scene->selected)
	{
		color.z += 0.2;
		color.z = clamp_number(color.z, 0 , 1);
	}
	return (color);
}

t_color	calc_ambient_contribution(t_color *ambient, t_color *obj, double ratio)
{
	t_color	ambient_contrib;

	ambient_contrib = vproduct_vec3(ambient, obj);
	ambient_contrib = product_vec3_r(&ambient_contrib, ratio);
	return (ambient_contrib);
	/* 
	ambient = product_vec3_r(&ambient, scene->amblight.ratio);
	pxl_color = add_vec3(&pxl_color, &ambient);
	pxl_color.x = clamp_number(pxl_color.x, 0, 1);
	pxl_color.y = clamp_number(pxl_color.y, 0, 1);
	pxl_color.z = clamp_number(pxl_color.z, 0, 1); */
}

t_color	render_raytrace_mode(t_scene *scene, t_world *hit_obj, t_hit*tmp_hit)
{
	t_world	*tmp_obj;
	t_ray	r_light;
	t_hit	hit;
	t_color pxl_color;
	t_color	diffuse_color;
	double	length_lray;
	double	ratio;

	pxl_color = calc_ambient_contribution(&scene->amblight.color, &hit_obj->color, scene->amblight.ratio);
	r_light.dir = substract_vec3(&scene->light->center, &tmp_hit->p);
	length_lray = length(&r_light.dir);
	r_light.dir = unit_vector(&r_light.dir);
	r_light.orig = tmp_hit->p;
	tmp_obj = scene->objs;
	while (tmp_obj)
	{
		hit.ray_tmin = 0.0001;
		hit.ray_tmax = length_lray;
		if (tmp_obj->hit(&r_light, tmp_obj->type, &hit))
		{
			return (pxl_color);
		}
		tmp_obj = tmp_obj->next;
	}

	ratio = dot(&tmp_hit->normal, &r_light.dir);
	diffuse_color = hit_obj->color;
	product_vec3(&diffuse_color, ratio);
	product_vec3(&diffuse_color, scene->light->bright);
	division_vec3(&diffuse_color, length_lray * length_lray);
	pxl_color = add_vec3(&pxl_color, &diffuse_color);
	return (pxl_color);
}

//contribution = sphereColor * dot(N, L) * lightIntensity / distanceToLight^2;
