/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:16:21 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/24 16:13:35 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

// reflected_ray.dir = v - 2*dot(v,n)*n;
static t_ray	calc_reflected_ray(t_hit *hit_rec, const t_ray *r)
{
	t_ray	reflected;

	reflected.orig = product_vec3_r(&hit_rec->normal, BIAS);
	reflected.orig = add_vec3(&hit_rec->p, &reflected.orig);
	reflected.dir = product_vec3_r(&hit_rec->normal, 2 * dot(&r->dir, &hit_rec->normal)); //unit vectors or not
	reflected.dir = substract_vec3(&r->dir, &reflected.dir); //unit vectors or not
	return (reflected);
}

static t_hit	find_closest_intersection(t_scene *scene, const t_ray *r_reflected)
{
	t_world	*obj;
	t_hit	hit_rec;

	obj = scene->objs;
	hit_rec.obj = NULL;
	hit_rec.ray_tmin = BIAS;
	hit_rec.ray_tmax = INT_MAX;
	while (obj)
	{
		if (obj->hit(r_reflected, obj->type, &hit_rec))
		{
			hit_rec.ray_tmax = hit_rec.t;
			hit_rec.obj = obj;
		}
		obj = obj->next;
	}
	return (hit_rec);
}

t_color	calc_reflected_color(t_scene *scene, t_hit *hit_rec, const t_ray *r, int ray_depth)
{
	t_color	reflect;
	t_ray	r_reflected;
	t_hit	r_hit_rec;

	reflect = (t_color){0, 0, 0};
	if (hit_rec->obj->materia.metallic > 0.0)
	{
		r_reflected = calc_reflected_ray(hit_rec, r);
		r_hit_rec = find_closest_intersection(scene, &r_reflected);
		if (r_hit_rec.obj)
			reflect = render_raytrace_mode(scene, &r_reflected, &r_hit_rec, ray_depth - 1);
		product_vec3(&reflect, hit_rec->obj->materia.metallic);
	}
	return (reflect);
}

