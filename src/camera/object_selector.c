/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_selector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:41:32 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/03 20:57:11 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_world	*select_object(t_scene *scene, int x, int y)
{
	t_camera	*camera;
	t_vec3		tmp_i;
	t_vec3		tmp_j;
	t_point3	pixel_center;
	t_ray		r;

	camera = &scene->camera;
	tmp_i = product_vec3_r(&camera->pixel_delta_u, x);
	tmp_j = product_vec3_r(&camera->pixel_delta_v, y);
	pixel_center = add_vec3(&camera->pixel00_loc, &tmp_i);
	pixel_center = add_vec3(&pixel_center, &tmp_j);
	r.orig = camera->center;
	r.dir = substract_vec3(&pixel_center, &camera->center);
	return (send_selector_ray(&r, scene));
}

t_world	*send_selector_ray(t_ray *r, t_scene *scene)
{
	t_hit	tmp_hit;
	t_world	*objs;
	t_world	*hit_obj;
	
	hit_obj = NULL;
	tmp_hit.ray_tmin = 0;
	tmp_hit.ray_tmax = INT_MAX;
	objs = scene->objs;
	while (objs)
	{
		if (objs->hit(r, objs->type, &tmp_hit))
		{
			tmp_hit.ray_tmax = tmp_hit.t;
			hit_obj = objs;
		}
		objs = objs->next;
	}
	return (hit_obj);
}
