/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:54:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/13 19:26:31 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"


t_color	calc_specular_light(t_scene *scene, const t_ray *r, t_ray *r_light, t_hit *tmp_hit, double len_sqrd)
{
	t_color	specular;
	t_vec3	reflected;
	t_vec3	view_dir;
	double	tmp;
	double	specular_strength;

	t_vec3	unit_light_dir = unit_vector(&r_light->dir);
	tmp = 2 * dot(&unit_light_dir, &tmp_hit->normal);
	reflected = product_vec3_r(&tmp_hit->normal, tmp);
	reflected = substract_vec3(&tmp_hit->normal, &unit_light_dir);
	reflected = unit_vector(&reflected);

	view_dir = unit_vector(&r->dir);
	view_dir = product_vec3_r(&r->dir, -1);

	specular_strength = ft_max(dot(&reflected, &view_dir), 0);
	specular_strength = pow(specular_strength, 32);
	specular = product_vec3_r(&scene->light->color, specular_strength);
	//specular = product_vec3_r(&specular, scene->light->bright);
	(void)len_sqrd;
	specular = division_vec3_r(&specular, len_sqrd);
	return (specular);
}

//ambient = ambient.color * obj.color * ambient.brightness
t_color	calc_ambient_light(t_color *ambient, t_color *obj, double ratio)
{
	t_color	ambient_light;

	ambient_light = vproduct_vec3(ambient, obj);
	ambient_light = product_vec3_r(&ambient_light, ratio);
	return (ambient_light);
}
// diffuse = (color(obj) * color(light) * ratio(angle) * brightness) / (distance ^ 2)
t_color	calc_diffuse_light(t_scene *scene, t_ray *r_light, t_hit *tmp_hit, double len_sqrd, t_world *hit_obj)
{
	t_color	diffuse_color;
	double	angle_ratio;
	t_vec3	unit_light_dir;

	unit_light_dir = unit_vector(&r_light->dir);
	diffuse_color = vproduct_vec3(&hit_obj->color, &scene->light->color);
	angle_ratio = ft_max(dot(&tmp_hit->normal, &unit_light_dir), 0);
	product_vec3(&diffuse_color, angle_ratio);
	product_vec3(&diffuse_color, scene->light->bright);
	division_vec3(&diffuse_color, len_sqrd);
	return (diffuse_color);
}

bool	calc_hard_shadows(t_world *objs, t_ray *r_light, double len_sqrd)
{
	t_hit	hit;

	while (objs)
	{
		hit.ray_tmin = 0.00001;
		hit.ray_tmax = len_sqrd;
		if (objs->hit(r_light, objs->type, &hit))
			return (true);
		objs = objs->next;
	}
	return (false);
}
