/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:59:07 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/16 19:55:24 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

// SEND OBJ BY ADDRESS
bool	hit_sphere(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_sphere	*sp;
	t_vec3		oc;
	t_evars		vars;

	sp = obj.sp;
	oc = substract_vec3(&ray->orig, &sp->center);
	vars.a = length_squared(&ray->dir);
	vars.half_b = dot(&oc, &ray->dir);
	vars.c = length_squared(&oc) - (sp->radius * sp->radius);
	vars.discriminant = (vars.half_b * vars.half_b) - (vars.a * vars.c);
	vars.sqrtd = sqrt(vars.discriminant);
	if (vars.discriminant < 0)
		return (false);
	vars.root = (-vars.half_b - vars.sqrtd) / vars.a;
	if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
	{
		vars.root = (-vars.half_b + vars.sqrtd) / vars.a;
		if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
			return (false);
	}
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	rec->normal = substract_vec3(&rec->p, &sp->center);
	division_vec3(&rec->normal, sp->radius);
	return (true);
}
