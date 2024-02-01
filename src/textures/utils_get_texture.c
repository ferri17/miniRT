/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:50:54 by apriego-          #+#    #+#             */
/*   Updated: 2024/02/01 14:54:08 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3	point_rot(t_vec3 *dir_o, t_vec3 *dir_y, t_vec3 *p_hit, t_point3 *center)
{
	double		tmp;
	double		theta;
	t_vec3		tmp_vec;
	t_vec3		rotation_axiz;
	t_matrix3x3	mat_rot;

	tmp = dot(dir_o, dir_y) / (length(dir_o) * length(dir_y));
	theta = acos(tmp);
	tmp_vec = cross(dir_o, dir_y);
	rotation_axiz = division_vec3_r(&tmp_vec, length(&tmp_vec));
	rotation_axiz = unit_vector(&rotation_axiz);
	mat_rot = calculate_rotation_matrix(theta, &rotation_axiz);
	return (rotate_point(p_hit, center, &mat_rot));
}

t_color	get_cn_chess(t_vec3 *p_hit, t_world *objs, t_point3 *cent)
{
	t_uv		uv;
	t_point3	rot_p_hit;
	t_point3	axis;

	axis = (t_point3){0, 1, 0};
	uv.u = 0;
	uv.v = 0;
	if (fabs(dot(&objs->type.cn->dir, &axis)) < 0.95)
	{
		rot_p_hit = point_rot(&objs->type.cn->dir, &axis, p_hit, cent);
		uv = get_cylinder_map(&rot_p_hit, cent, objs->type.cn->height / 2);
	}
	else
		uv = get_cylinder_map(p_hit, cent, objs->type.cn->height / 2);
	uv.u *= 4;
	uv.v *= 2;
	return (checker_color(uv, objs->materia.color));
}

t_color	get_cn_bit(t_vec3 *p_hit, t_world *objs, t_point3 *cent,
		t_img_tex *texture)
{
	t_uv		uv;
	t_point3	rot_p_hit;
	t_point3	axis;

	axis = (t_point3){0, 1, 0};
	ft_bzero(&uv, sizeof(t_uv));
	if (fabs(dot(&objs->type.cn->dir, &axis)) < 0.95)
	{
		rot_p_hit = point_rot(&objs->type.cn->dir, &axis, p_hit, cent);
		uv = get_cylinder_map(&rot_p_hit, cent, objs->type.cn->height);
	}
	else
		uv = get_cylinder_map(p_hit, cent, objs->type.cn->height);
	return (map_uv_to_color(&uv, texture));
}

t_color	get_cy_chess(t_vec3 *p_hit, t_world *objs, t_point3 *cent)
{
	t_uv		uv;
	t_point3	rot_p_hit;
	t_point3	axis;

	axis = (t_point3){0, 1, 0};
	uv.u = 0;
	uv.v = 0;
	if (fabs(dot(&objs->type.cy->dir, &axis)) < 0.95)
	{
		rot_p_hit = point_rot(&objs->type.cy->dir, &axis, p_hit, cent);
		uv = get_cylinder_map(&rot_p_hit, cent, objs->type.cy->radius);
	}
	else
		uv = get_cylinder_map(p_hit, cent, objs->type.cy->radius);
	uv.u *= 4;
	uv.v *= 2;
	return (checker_color(uv, objs->materia.color));
}

t_color	get_cy_bit(t_vec3 *p_hit, t_world *objs, t_point3 *cent,
		t_img_tex *texture)
{
	t_uv		uv;
	t_point3	rot_p_hit;
	t_point3	axis;

	axis = (t_point3){0, 1, 0};
	uv.u = 0;
	uv.v = 0;
	if (fabs(dot(&objs->type.cy->dir, &axis)) < 0.95)
	{
		rot_p_hit = point_rot(&objs->type.cy->dir, &axis, p_hit, cent);
		uv = get_cylinder_map(&rot_p_hit, cent, objs->type.cy->height / 2);
	}
	else
		uv = get_cylinder_map(p_hit, cent, objs->type.cy->height / 2);
	return (map_uv_to_color(&uv, texture));
}
