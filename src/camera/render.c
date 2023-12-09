/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/09 13:29:09 by fbosch           ###   ########.fr       */
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


t_color	render_raytrace_mode(t_scene *scene, t_world *hit_obj, t_hit* hit_rec)
{
	t_ray	r_light;
	t_color pxl_color;
	t_color	diffuse_color;
	double	length_lray;

	pxl_color = calc_ambient_light(&scene->amblight.color, &hit_obj->color, scene->amblight.ratio);
	r_light.dir = substract_vec3(&scene->light->center, &hit_rec->p);
	length_lray = length(&r_light.dir);
	r_light.dir = unit_vector(&r_light.dir);
	r_light.orig = hit_rec->p;
	if (calc_hard_shadows(scene->objs, &r_light, length_lray))
		return (pxl_color);
	diffuse_color = calc_diffuse_light(scene, &r_light, hit_rec, length_lray, hit_obj);
	pxl_color = add_vec3(&pxl_color, &diffuse_color);
	return (pxl_color);
}

//contribution = sphereColor * dot(N, L) * lightIntensity / distanceToLight^2;
