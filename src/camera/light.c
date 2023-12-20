/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:54:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/20 17:22:05 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

//specular = lights.color * lights.brightness * dot(vReflected,vView) ^ roughness;
//Reflected = 2 * dot(Normal, Light) * vNormal - vLight 
t_color	calc_specular_light(t_light *lights, const t_ray *r, t_ray *r_light, t_hit *hit_rec, double len_sqrd)
{
	t_color	specular;
	t_vec3	reflected;
	t_vec3	view_dir;
	double	tmp;
	double	specular_strength;

	tmp = 2 * dot(&r_light->dir, &hit_rec->normal);
	reflected = product_vec3_r(&hit_rec->normal, tmp);
	reflected = substract_vec3(&reflected, &r_light->dir);
	reflected = unit_vector(&reflected);

	view_dir = unit_vector(&r->dir);
	view_dir = product_vec3_r(&view_dir, -1);

	specular_strength = ft_max(dot(&reflected, &view_dir), 0);
	// if (specular_strength > 0.05)
	// 	printf("s: %f\n", specular_strength);
	specular_strength = pow(specular_strength, 32);
	specular = product_vec3_r(&lights->color, specular_strength * 0.2);
	//specular = division_vec3_r(&specular, len_sqrd);
	(void)len_sqrd;
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
t_color	calc_diffuse_light(t_light *lights, t_ray *r_light, t_hit *tmp_hit, double len_sqrd, t_world *hit_obj)
{
	t_color	diffuse_color;
	double	angle_ratio;

	diffuse_color = vproduct_vec3(&hit_obj->color, &lights->color);
	angle_ratio = ft_max(dot(&tmp_hit->normal, &r_light->dir), 0);
	product_vec3(&diffuse_color, angle_ratio);
	product_vec3(&diffuse_color, lights->bright);
	//division_vec3(&diffuse_color, len_sqrd);
	(void)len_sqrd;
	return (diffuse_color);
}

bool	calc_hard_shadows(t_world *objs, t_ray *r_light, double max_len)
{
	t_hit	hit;

	while (objs)
	{
		hit.ray_tmin = 0; //small value glitch
		hit.ray_tmax = max_len;
		if (objs->hit(r_light, objs->type, &hit))
			return (true);
		objs = objs->next;
	}
	return (false);
}
