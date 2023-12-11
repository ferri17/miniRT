/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:00:29 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/11 18:08:11 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3	calculate_normal_cone(t_cone *cn, const t_vec3 *p)
{
	t_vec3	tmp;
	t_vec3	tmp1;
	t_vec3	tmp2;
	t_vec3	outward_normal;

	tmp = substract_vec3(p, &cn->apex);
	tmp1 = product_vec3_r(&cn->dir, dot(&cn->dir, &tmp));
	tmp2 = substract_vec3(&tmp, &tmp1);
	outward_normal = division_vec3_r(&tmp2, cn->angle / 2 * dot(&cn->dir,
				&tmp));
	return (outward_normal);
}

bool	hit_cone(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_vec3	oc;
	t_evars	vars;
	double	half_a;
	t_vec3	tmp;
	double	hit_z;
	t_vec3	outward_normal;

	oc = substract_vec3(&ray->orig, &obj.cn->apex);
	half_a = tan(obj.cn->angle / 2);
	vars.a = length_squared(&ray->dir) - (1 + half_a * half_a)
		* pow(dot(&ray->dir, &obj.cn->dir), 2);
	vars.half_b = 2 * (dot(&oc, &ray->dir) - (1 + half_a * half_a)
			* dot(&oc, &obj.cn->dir) * dot(&ray->dir, &obj.cn->dir));
	vars.c = length_squared(&oc) - (1 + half_a * half_a)
		* pow(dot(&oc, &obj.cn->dir), 2);
	vars.discriminant = vars.half_b * vars.half_b - 4 *	vars.a * vars.c;
	if (vars.discriminant < 0)
		return (false);
	vars.sqrtd = sqrt(vars.discriminant);
	vars.root = (-vars.half_b - vars.sqrtd) / (2 * vars.a);
	if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
	{
		vars.root = (-vars.half_b + vars.sqrtd) / (2 * vars.a);
		if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
			return (false);
	}
	tmp = product_vec3_r(&ray->dir, vars.root);
	tmp = add_vec3(&ray->orig, &tmp);
	tmp = substract_vec3(&tmp, &obj.cn->apex);
	hit_z = dot(&tmp, &obj.cn->dir);
	if (hit_z < 0 || hit_z > obj.cn->height)
		return (false);
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	outward_normal = calculate_normal_cone(obj.cn, &rec->p);
	if (dot(&ray->dir, &outward_normal) < 0)
		rec->normal = outward_normal;
	else
		rec->normal = product_vec3_r(&outward_normal, -1);
	return (true);
}
