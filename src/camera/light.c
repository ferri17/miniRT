/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:54:17 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/31 18:10:29 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

// reflected = 2 * dot(Normal, Light) * vNormal - vLight
// specular = lights.color * lights.brightness * dot(vReflec,vView) ^ roughnss;
t_color	calc_specular_light(t_light *lights, const t_ray *r, t_ray *r_light,
		t_hit *hit_rec)
{
	t_color	specular;
	t_vec3	reflected;
	t_vec3	view_dir;
	double	tmp;
	double	specular_strngth;

	tmp = 2 * dot(&r_light->dir, &hit_rec->normal);
	reflected = product_vec3_r(&hit_rec->normal, tmp);
	reflected = substract_vec3(&reflected, &r_light->dir);
	reflected = unit_vector(&reflected);
	view_dir = product_vec3_r(&r->dir, -1);
	specular_strngth = ft_max(dot(&reflected, &view_dir), 0);
	specular_strngth = pow(specular_strngth, hit_rec->obj->materia.roughness);
	specular = product_vec3_r(&lights->color, specular_strngth
			* lights->bright);
	product_vec3(&specular, hit_rec->obj->materia.specular);
	return (specular);
}

// ambient = ambient.color * obj.color * ambient.brightness
t_color	calc_ambient_light(t_color *ambient, t_color *obj, double ratio)
{
	t_color	ambient_light;

	ambient_light = vproduct_vec3(ambient, obj);
	ambient_light = product_vec3_r(&ambient_light, ratio);
	return (ambient_light);
}

// diffuse = (color(obj) * color(light) * ratio(angle) * brightness) *
//  ??diffuse_ratio?? / (1 + dst ^ 2)
t_color	calc_diffuse_light(t_light *lights, t_ray *r_light, t_hit *hit_rec)
{
	t_color	obj_color;
	t_color	diffuse_color;
	double	angle_ratio;

	obj_color = hit_rec->obj->get_color(&hit_rec->p, hit_rec->obj,
			hit_rec->obj->materia.bit);
	diffuse_color = vproduct_vec3(&obj_color, &lights->color);
	angle_ratio = ft_max(dot(&hit_rec->normal, &r_light->dir), 0);
	product_vec3(&diffuse_color, angle_ratio);
	product_vec3(&diffuse_color, lights->bright);
	return (diffuse_color);
}

bool	calc_hard_shadows(t_world *objs, t_ray *r_light, t_hit *hit_rec)
{
	t_hit	hit;

	if (dot(&r_light->dir, &hit_rec->normal) < BIAS)
		return (true);
	hit.ray_tmin = 0;
	hit.ray_tmax = sqrt(r_light->len_sqrd) + BIAS;
	while (objs)
	{
		if (objs->hit(r_light, objs->type, &hit))
			return (true);
		objs = objs->next;
	}
	return (false);
}
