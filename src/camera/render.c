/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/06 13:13:27 by fbosch           ###   ########.fr       */
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

t_color	render_raytrace_mode(t_scene *scene, t_hit*tmp_hit)
{
	t_world	*tmp_obj;
	t_vec3	light_dir;
	t_ray	r_light;
	t_color	color;

	color = (t_color){0, 0, 0};
	tmp_obj = scene->objs;
	light_dir = substract_vec3(&scene->light->center, &tmp_hit->p);
	r_light.orig = scene->light->center;
	r_light.dir = unit_vector(&light_dir);
	while (tmp_obj)
	{
		tmp_hit->ray_tmin = 0;
		tmp_hit->ray_tmin = INT_MAX;
		if (tmp_obj->hit(&r_light, tmp_obj->type, tmp_hit))
		{
			return (color);
		}
		tmp_obj = tmp_obj->next;
	}
	double	ratio = dot(&tmp_hit->normal, &r_light.dir);
	color = (t_color){ratio, ratio, ratio};
	return (color);
}
