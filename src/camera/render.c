/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/06 18:03:05 by fbosch           ###   ########.fr       */
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

t_color	render_raytrace_mode(t_scene *scene, t_world *hit_obj, t_hit*tmp_hit)
{
	//t_world	*tmp_obj;
	t_ray	r_light;
	t_hit	ahit;

	r_light.dir = substract_vec3(&scene->light->center, &tmp_hit->p);
	r_light.dir = unit_vector(&r_light.dir);
	r_light.orig = scene->light->center;

	(void)hit_obj;
	(void)ahit;
	/* tmp_obj = scene->objs;
	while (tmp_obj)
	{
		ahit.ray_tmin = 0;
		ahit.ray_tmax = INT_MAX;
		if (hit_obj != tmp_obj && tmp_obj->hit(&r_light, tmp_obj->type, &ahit))
		{
			return ((t_color){0, 0, 0});
		}
		tmp_obj = tmp_obj->next;
	} */
	double	ratio = dot(&tmp_hit->normal, &r_light.dir);
	t_color sphere_color;
	sphere_color = hit_obj->color;
	product_vec3(&sphere_color, ratio);
	product_vec3(&sphere_color, scene->light->bright);
	t_vec3	tmp10 = substract_vec3(&scene->light->center, &tmp_hit->p);
	double distance = length(&tmp10);
	division_vec3(&sphere_color, distance / 2);
	sphere_color.x = sphere_color.x / (double)255;
	sphere_color.x = sphere_color.y / (double)255;
	sphere_color.x = sphere_color.z / (double)255;
	return (sphere_color);
}

//contribution = sphereColor * dot(N, L) * lightIntensity / distanceToLight^2;
