/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:00:29 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/11 15:36:47 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3	calculate_normal_cone(t_cone *cn, const t_vec3 *p)
{
	t_vec3	apex_to_point;
	t_vec3	projected;
	t_vec3	outward_normal;

	apex_to_point = substract_vec3(p, &cn->apex);
	t_vec3 inv_dir = product_vec3_r(&cn->dir, -1);
	projected = product_vec3_r(&inv_dir, dot(&inv_dir, &apex_to_point));
	outward_normal = substract_vec3(&apex_to_point, &projected);
	return (unit_vector(&outward_normal));
}

bool	calc_hit_cone(const t_ray *ray, t_objects obj, t_hit *rec, t_evars vars)
{
	double	hit_z;
	t_vec3	tmp;
	t_vec3	outward_normal;

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
	rec->normal = outward_normal;
	return (true);
}

bool	hit_cone(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_vec3	oc;
	t_evars	vars;
	double	half_a;

	oc = substract_vec3(&ray->orig, &obj.cn->apex);
	half_a = tan(obj.cn->angle / 2.0);
	vars.a = length_squared(&ray->dir) - (1 + half_a * half_a)
		* pow(dot(&ray->dir, &obj.cn->dir), 2);
	vars.half_b = 2 * (dot(&oc, &ray->dir) - (1 + half_a * half_a)
			* dot(&oc, &obj.cn->dir) * dot(&ray->dir, &obj.cn->dir));
	vars.c = length_squared(&oc) - (1 + half_a * half_a)
		* pow(dot(&oc, &obj.cn->dir), 2);
	vars.discriminant = vars.half_b * vars.half_b - 4 * vars.a * vars.c;
	if (vars.discriminant < 0)
		return (false);
	vars.sqrtd = sqrt(vars.discriminant);
	return (calc_hit_cone(ray, obj, rec, vars));
}

bool	hit_disk_cone(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_ray		displace;
	t_disk		disk;

	displace.dir = obj.cn->dir;
	displace.orig = obj.cn->center;
	obj.cn->apex = ray_at(&displace, -(obj.cn->height / 2));
	disk.radius = tan(obj.cn->angle / 2) * obj.cn->height;
	disk.center = ray_at(&displace, obj.cn->height / 2);
	disk.dir = obj.cn->dir;
	obj.cn->hit[H_CONE] = hit_cone(ray, obj, rec);
	if (obj.cn->hit[H_CONE])
		rec->ray_tmax = rec->t;
	obj.cn->hit[H_DISK] = hit_disk(ray, &disk, rec);
	return (obj.cn->hit[H_CONE] || obj.cn->hit[H_DISK]);
}
