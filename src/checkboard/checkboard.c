/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/18 12:38:09 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	get_color_sphere(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;

	uv = get_spherical_map(p_hit, &objs->type.sp->center,
			objs->type.sp->radius);
	uv.u *= 4;
	uv.v *= 2;
	return (checker_color(uv, objs->materia.color));
}

t_color	get_color_plane(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;

	uv = get_planar_map(p_hit, &objs->type.pl->normal, &objs->type.pl->center);
	return (checker_color(uv, objs->materia.color));
}

t_color	get_color_cone(t_vec3 *p_hit, t_world *objs)
{
	t_color	color;
	t_uv	uv;

	if (objs->type.cn->hit[H_CONE])
	{
		uv = get_cylinder_map(p_hit, &objs->type.cn->center);
		uv.u *= 6;
		uv.v *= 2;
		return (checker_color(uv, objs->materia.color));
	}
	else
	{
		uv = get_planar_map(p_hit, &objs->type.cn->dir, &objs->type.pl->center);
		uv.u *= 6;
		uv.v *= 2;
		return (checker_color(uv, objs->materia.color));
	}
	return (color);
}

t_color	checker_color_cylinder(t_uv uv, t_color color)
{
	int	u_int;
	int	v_int;

	u_int = uv.u * 8;
	v_int = uv.v * 8;
	if (((u_int % 2) == 0) ^ ((v_int % 2) == 0))
		return (color);
	return ((t_color){0, 0, 0});
}

t_color	get_color_cylinder(t_vec3 *p_hit, t_world *objs)
{
	t_uv		uv;
	t_point3	center;
	t_ray		ray;

	ray.dir = objs->type.cy->dir;
	ray.orig = objs->type.cy->center;
	center = ray_at(&ray, objs->type.cy->height / 2);
	uv = get_cylinder_map(p_hit, &center);
	uv.u *= 2;
	return (checker_color_cylinder(uv, objs->materia.color));
}
