/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/24 20:38:29 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	get_color_sphere(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;

	if (objs->materia.texture == DEFAULT)
	{
		uv = get_spherical_map(p_hit, &objs->type.sp->center,
			objs->type.sp->radius);
		
		printf("%f, %f\n", uv.u, uv.v);
		uv.u = floor((uv.u + 1) * (objs->materia.img_tex.w / 2));
		uv.v = floor((uv.v + 1) * (objs->materia.img_tex.h / 2));
		int pixel = (objs->materia.img_tex.sl * 49) + (objs->materia.img_tex.bpp * 49 / 8);
		int b = objs->materia.img_tex.info[pixel + 0];
		int g = objs->materia.img_tex.info[pixel + 1];
		int r = objs->materia.img_tex.info[pixel + 2];
		
		double bb = (double)b / 255;
		double gg = (double)g / 255; 
		double rr = (double)r / 255; 


		return ((t_color){rr, gg, bb});
		return ((t_color){objs->materia.img_tex.info[pixel + 2], objs->materia.img_tex.info[pixel + 1], objs->materia.img_tex.info[pixel + 0]});
		//pixel = (data->img.line_bytes * y) + (x * data->img.pixel_bits / 8);

		return (objs->materia.color);
	}
	uv = get_spherical_map(p_hit, &objs->type.sp->center,
			objs->type.sp->radius);
	//printf("%f, %f\n", uv.u, uv.v);
	uv.u *= 4;
	uv.v *= 2;
	return (checker_color(uv, objs->materia.color));
}

t_color	get_color_plane(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;

	if (objs->materia.texture == DEFAULT)
		return (objs->materia.color);
	uv = get_planar_map(p_hit, &objs->type.pl->normal, &objs->type.pl->center);
	//printf("%f, %f\n", uv.u, uv.v);
	return (checker_color(uv, objs->materia.color));
}

t_vec3	point_rot(t_vec3 *dir_o, t_vec3 *dir_y, t_vec3 *p_hit, t_point3 *center)
{
	double		tmp;
	double		theta;
	t_vec3		tmp_vec;
	t_vec3		rotation_axiz;
	t_matrix3x3	mat_rot;

	tmp = dot(dir_o, dir_y)
		/ (length(dir_o) * length(dir_y));
	theta = acos(tmp);
	tmp_vec = cross(dir_o, dir_y);
	rotation_axiz = division_vec3_r(&tmp_vec, length(&tmp_vec));
	rotation_axiz = unit_vector(&rotation_axiz);
	mat_rot = calculate_rotation_matrix(theta, &rotation_axiz);
	return (rotate_point(p_hit, center, &mat_rot));
}

t_color	get_color_cone(t_vec3 *p_hit, t_world *objs)
{
	t_uv		uv;
	t_point3	cent;
	t_ray		ray;
	t_point3	rot_p_hit;

	ray.dir = objs->type.cn->dir;
	ray.orig = objs->type.cn->center;
	cent = ray_at(&ray, objs->type.cn->height / 2);
	if (objs->materia.texture == DEFAULT)
		return (objs->materia.color);
	if (objs->type.cn->hit[H_CONE])
	{
		if (fabs(dot(&objs->type.cn->dir, &(t_point3){0, 1, 0})) < 0.95)
		{
			rot_p_hit = point_rot(&ray.dir, &(t_point3){0, 1, 0}, p_hit, &cent);
			uv = get_cylinder_map(&rot_p_hit, &cent, objs->type.cn->height);
		}
		else
			uv = get_cylinder_map(p_hit, &cent, objs->type.cn->height);
		uv.u *= 2;
		uv.v *= 4;
	}
	else
		uv = get_planar_map(p_hit, &objs->type.cn->dir, &cent);
	return (checker_color(uv, objs->materia.color));
}

t_color	get_color_cylinder(t_vec3 *p_hit, t_world *objs)
{
	t_uv		uv;
	t_point3	cent;
	t_ray		ray;
	t_point3	rot_p_hit;

	ray.dir = objs->type.cy->dir;
	ray.orig = objs->type.cy->center;
	cent = ray_at(&ray, objs->type.cy->height / 2);
	if (objs->materia.texture == DEFAULT)
		return (objs->materia.color);
	if (objs->type.cy->hit[H_CYLINDER])
	{
		if (fabs(dot(&objs->type.cy->dir, &(t_point3){0, 1, 0})) < 0.95)
		{
			rot_p_hit = point_rot(&ray.dir, &(t_point3){0, 1, 0}, p_hit, &cent);
			uv = get_cylinder_map(&rot_p_hit, &cent, objs->type.cy->radius);
		}
		else
			uv = get_cylinder_map(p_hit, &cent, objs->type.cy->radius);
		uv.u *= 4;
		uv.v *= 2;
	}
	else
		uv = get_planar_map(p_hit, &objs->type.cy->dir, &cent);
	return (checker_color(uv, objs->materia.color));
}
