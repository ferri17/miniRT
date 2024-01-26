/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/26 13:54:17 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	map_uv_to_color(t_uv *uv, t_img_tex *img_tex)
{
	unsigned int	i;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	t_color			color;

	uv->u = floor(uv->u * img_tex->w);
	uv->v = floor(uv->v * img_tex->h);
	i = (img_tex->sl * uv->v) + (img_tex->bpp * uv->u / 8);
	if (i >= (unsigned int)(img_tex->sl * img_tex->h))
		return ((t_color){0,0,0});
	b = (unsigned char)img_tex->info[i + 0];
	g = (unsigned char)img_tex->info[i + 1];
	r = (unsigned char)img_tex->info[i + 2];
	color.z = (double)b / 255.999;
	color.y = (double)g / 255.999; 
	color.x = (double)r / 255.999;
	return (color);
}

t_color	get_color_sphere(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;
	t_color	color;

	if (objs->materia.texture == DEFAULT || objs->materia.texture == BUMPMAP)
		return (objs->materia.color);
	color = (t_color){0,0,0};
	uv = get_spherical_map(p_hit, &objs->type.sp->center,
		objs->type.sp->radius);
	if (objs->materia.texture == BITMAP || objs->materia.texture == BITMAP_BUMPMAP)
		color = map_uv_to_color(&uv, &objs->materia.bit);
	else if (objs->materia.texture == CHECKBOARD)
	{
		uv.u *= 4;
		uv.v *= 2;
		color = checker_color(uv, objs->materia.color);
	}
	return (color);
}
/*
	t_uv	uv;
	t_color	color;

	if (objs->materia.texture == DEFAULT || objs->materia.texture == BUMPMAP)
		return (objs->materia.color);
	color = (t_color){0,0,0};
	uv = get_planar_map(p_hit, &objs->type.pl->normal, &objs->type.pl->center);
	if (objs->materia.texture == BITMAP || objs->materia.texture == BITMAP_BUMPMAP)
		color = map_uv_to_color(&uv, &objs->materia.bit);
	else if (objs->materia.texture == CHECKBOARD)
		color = checker_color(uv, objs->materia.color);
	return (color);
*/
t_color	get_color_plane(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;
	t_color	color;

	if (objs->materia.texture == DEFAULT || objs->materia.texture == BUMPMAP)
		return (objs->materia.color);
	color = (t_color){0,0,0};
	uv = get_planar_map(p_hit, &objs->type.pl->normal, &objs->type.pl->center);
	if (objs->materia.texture == BITMAP || objs->materia.texture == BITMAP_BUMPMAP)
	{
		uv.u = uv.u - floor(uv.u);
		uv.v = uv.v - floor(uv.v);
		color = map_uv_to_color(&uv, &objs->materia.bit);
	}
	else if (objs->materia.texture == CHECKBOARD)
		color = checker_color(uv, objs->materia.color);
	return (color);
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
	t_color		color;

	ray.dir = objs->type.cy->dir;
	ray.orig = objs->type.cy->center;
	cent = ray_at(&ray, objs->type.cy->height / 2);
	uv.u = 0;
	uv.v = 0;
	if (objs->materia.texture == CHECKBOARD)
	{
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
		else if (objs->type.cy->hit[H_DISK_TA] || objs->type.cy->hit[H_DISK_BA])
	 		uv = get_planar_map(p_hit, &objs->type.cy->dir, &cent);
		color = checker_color(uv, objs->materia.color);
	}
	else if (objs->materia.texture == BITMAP || objs->materia.texture == BITMAP_BUMPMAP)
	{
	 	if (objs->type.cy->hit[H_CYLINDER])
	 	{
	 		if (fabs(dot(&objs->type.cy->dir, &(t_point3){0, 1, 0})) < 0.95)
	 		{
	 			rot_p_hit = point_rot(&ray.dir, &(t_point3){0, 1, 0}, p_hit, &cent);
	 			uv = get_cylinder_map(&rot_p_hit, &cent, objs->type.cy->radius);
	 		}
	 		else
	 			uv = get_cylinder_map(p_hit, &cent, objs->type.cy->radius);
	 	}
		else if (objs->type.cy->hit[H_DISK_TA] || objs->type.cy->hit[H_DISK_BA])
		{
	 		uv = get_planar_map(p_hit, &objs->type.cy->dir, &cent);
	 		uv.u = uv.u - floor(uv.u);
	 		uv.v = uv.v - floor(uv.v);
		}
		color = map_uv_to_color(&uv, &objs->materia.bit);
	}
 	else
 		return (objs->materia.color);
	return (color);
}
