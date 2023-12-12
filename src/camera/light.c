/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:54:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/12 01:58:11 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	calc_specular_light(t_scene *scene, const t_ray *r, t_ray *r_light, t_hit *tmp_hit, double length_lray)
{
	t_color	specular;
	t_vec3	reflected;
	t_vec3	in_light_dir;
	t_vec3	unit_view;
	double	tmp;

	in_light_dir = product_vec3_r(&r_light->dir, -1);
	tmp = 2 * dot(&in_light_dir, &tmp_hit->normal);
	reflected = product_vec3_r(&tmp_hit->normal, tmp);
	reflected = substract_vec3(&tmp_hit->normal, &in_light_dir);
	reflected = unit_vector(&reflected);
	unit_view = unit_vector(&r->dir);
	specular = product_vec3_r(&scene->light->color, clamp_number(dot(&reflected, &unit_view), 0, 1));
	specular = product_vec3_r(&specular, scene->light->bright);
	specular = division_vec3_r(&specular, length_lray * length_lray);
	return (specular);
}
t_color	calc_ambient_light(t_color *ambient, t_color *obj, double ratio)
{
	t_color	ambient_contrib;

	ambient_contrib = vproduct_vec3(ambient, obj);
	ambient_contrib = product_vec3_r(&ambient_contrib, ratio);
	return (ambient_contrib);
}
// diffuse = (color(obj) * color(light) * ratio(angle) * brightness) / (distance ^ 2)
t_color	calc_diffuse_light(t_scene *scene, t_ray *r_light, t_hit *tmp_hit, double length_lray, t_world *hit_obj)
{
	t_color	diffuse_color;
	double	ratio;

	diffuse_color = vproduct_vec3(&hit_obj->color, &scene->light->color);
	ratio = clamp_number(dot(&tmp_hit->normal, &r_light->dir), 0, 1);
	product_vec3(&diffuse_color, ratio);
	product_vec3(&diffuse_color, scene->light->bright);
	division_vec3(&diffuse_color, length_lray * length_lray);
	return (diffuse_color);
}

bool	calc_hard_shadows(t_world *objs, t_ray *r_light, double length_lray)
{
	t_hit	hit;

	while (objs)
	{
		hit.ray_tmin = 0.00001;
		hit.ray_tmax = length_lray;
		if (objs->hit(r_light, objs->type, &hit))
			return (true);
		objs = objs->next;
	}
	return (false);
}
