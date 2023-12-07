/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/07 20:12:55 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

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

t_color	calc_ambient_light(t_color *ambient, t_color *obj, double ratio)
{
	t_color	ambient_contrib;

	ambient_contrib = vproduct_vec3(ambient, obj);
	ambient_contrib = product_vec3_r(&ambient_contrib, ratio);
	return (ambient_contrib);
}

t_color	calc_diffuse_light(t_scene *scene, t_ray *r_light, t_hit *tmp_hit, double length_lray, t_world *hit_obj)
{
	t_color	diffuse_color;
	double	ratio;

	diffuse_color = vproduct_vec3(&hit_obj->color, &scene->light->color);
	ratio = dot(&tmp_hit->normal, &r_light->dir);
	product_vec3(&diffuse_color, ratio);
	product_vec3(&diffuse_color, scene->light->bright);
	division_vec3(&diffuse_color, length_lray * length_lray);
	return (diffuse_color);
}


t_color	render_raytrace_mode(t_scene *scene, t_world *hit_obj, t_hit* hit_rec)
{
	t_world	*tmp_obj;
	t_ray	r_light;
	t_hit	hit;
	t_color pxl_color;
	double	length_lray;

	pxl_color = calc_ambient_light(&scene->amblight.color, &hit_obj->color, scene->amblight.ratio);
	r_light.dir = substract_vec3(&scene->light->center, &hit_rec->p);
	length_lray = length(&r_light.dir);
	r_light.dir = unit_vector(&r_light.dir);
	r_light.orig = hit_rec->p;
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
	t_color	diffuse_color = calc_diffuse_light(scene, &r_light, hit_rec, length_lray, hit_obj);
	pxl_color = add_vec3(&pxl_color, &diffuse_color);
	return (pxl_color);
}

//contribution = sphereColor * dot(N, L) * lightIntensity / distanceToLight^2;
