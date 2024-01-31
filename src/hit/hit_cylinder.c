/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:52:37 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/31 19:34:45 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3	calculate_normal(const t_cylinder *cylinder, const t_point3 p)
{
	t_vec3	tmp;
	t_vec3	tmp2;
	t_vec3	normal;

	tmp = substract_vec3(&cylinder->center, &p);
	tmp2 = product_vec3_r(&cylinder->dir, dot(&tmp, &cylinder->dir));
	normal = substract_vec3(&tmp2, &tmp);
	return (unit_vector(&normal));
}

bool	calc_hit_cilinder(t_evars vars, const t_ray *ray, t_hit *rec,
		t_objects obj)
{
	double	projection;
	t_vec3	tmp;

	if (vars.discriminant < 0)
		return (false);
	vars.sqrtd = sqrt(vars.discriminant);
	vars.root = (-vars.half_b - vars.sqrtd) / vars.a;
	if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
	{
		vars.root = (-vars.half_b + vars.sqrtd) / vars.a;
		if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
			return (false);
	}
	tmp = ray_at(ray, vars.root);
	tmp = substract_vec3(&tmp, &obj.cy->center);
	projection = dot(&obj.cy->dir, &tmp);
	if (projection < 0 || projection > obj.cy->height)
		return (false);
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	rec->normal = calculate_normal(obj.cy, rec->p);
	return (true);
}

bool	hit_body_cylinder(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_vec3	oc;
	t_vec3	tmp;
	t_vec3	direction_parallel;
	t_vec3	oc_parallel;
	t_evars	vars;

	oc = substract_vec3(&ray->orig, &obj.cy->center);
	tmp = product_vec3_r(&obj.cy->dir, dot(&ray->dir, &obj.cy->dir));
	direction_parallel = substract_vec3(&ray->dir, &tmp);
	tmp = product_vec3_r(&obj.cy->dir, dot(&oc, &obj.cy->dir));
	oc_parallel = substract_vec3(&oc, &tmp);
	vars.a = length_squared(&direction_parallel);
	vars.half_b = dot(&oc_parallel, &direction_parallel);
	vars.c = length_squared(&oc_parallel) - obj.cy->radius * obj.cy->radius;
	vars.discriminant = vars.half_b * vars.half_b - vars.a * vars.c;
	return (calc_hit_cilinder(vars, ray, rec, obj));
}

bool	hit_cylinder(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_disk	disk;
	t_ray	displace;

	displace.orig = obj.cy->center;
	displace.dir = obj.cy->dir;
	disk.center = obj.cy->center;
	disk.dir = obj.cy->dir;
	disk.radius = obj.cy->radius;
	obj.cy->hit[H_DISK_BA] = hit_disk(ray, &disk, rec);
	if (obj.cy->hit[H_DISK_BA])
		rec->ray_tmax = rec->t;
	disk.center = ray_at(&displace, obj.cy->height);
	disk.dir = product_vec3_r(&obj.cy->dir, -1);
	obj.cy->hit[H_DISK_TA] = hit_disk(ray, &disk, rec);
	if (obj.cy->hit[H_DISK_TA])
		rec->ray_tmax = rec->t;
	obj.cy->hit[H_CYLINDER] = hit_body_cylinder(ray, obj, rec);
	return (obj.cy->hit[H_DISK_BA] || obj.cy->hit[H_DISK_TA]
		|| obj.cy->hit[H_CYLINDER]);
}
