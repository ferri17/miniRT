/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/19 12:23:08 by apriego-         ###   ########.fr       */
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
	t_color tmp_color;
	t_color	ambient_light;



	
	//if (calc_hard_shadows(scene->objs, &r_light, len_sqrd))
		//return (pxl_color);
		
	
	//pxl_color = specular_light;
	//pxl_color = add_vec3(&pxl_color, &specular_light);

	(void)r;
	if (hit_obj->materia.texture == CHECKBOARD)
	{
		tmp_color = hit_obj->get_color(hit_rec->p, hit_obj);
		ambient_light = calc_ambient_light(&scene->amblight.color, &tmp_color, scene->amblight.ratio);
	}
	else
	{
		ambient_light = calc_ambient_light(&scene->amblight.color, &hit_obj->materia.color, scene->amblight.ratio);
	}
	
	return (ambient_light);
}

//contribution = sphereColor * dot(N, L) * lightIntensity / distanceToLight^2;
