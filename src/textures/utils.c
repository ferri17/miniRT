/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:31:58 by apriego-          #+#    #+#             */
/*   Updated: 2024/02/04 18:31:35 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

double	quit_decimals(double num)
{
	return (num - floor(num));
}

t_color	checker_color(t_uv uv, t_color color)
{
	double	tmp1;
	double	tmp2;

	tmp1 = quit_decimals(uv.u);
	tmp2 = quit_decimals(uv.v);
	if ((tmp1 < 0.5) ^ (tmp2 < 0.5))
		return (color);
	else
		return ((t_color){0.0f, 0.0f, 0.0f});
}

t_matrix3x3	calculate_rotation_matrix(double angle, t_vec3 *axis)
{
	double		cos_theta;
	double		sin_theta;
	t_matrix3x3	r;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	r.m[0][0] = cos_theta + axis->x * axis->x * (1 - cos_theta);
	r.m[0][1] = axis->x * axis->y * (1 - cos_theta) - axis->z * sin_theta;
	r.m[0][2] = axis->x * axis->z * (1 - cos_theta) + axis->y * sin_theta;
	r.m[1][0] = axis->y * axis->x * (1 - cos_theta) + axis->z * sin_theta;
	r.m[1][1] = cos_theta + axis->y * axis->y * (1 - cos_theta);
	r.m[1][2] = axis->y * axis->z * (1 - cos_theta) - axis->x * sin_theta;
	r.m[2][0] = axis->z * axis->x * (1 - cos_theta) - axis->y * sin_theta;
	r.m[2][1] = axis->z * axis->y * (1 - cos_theta) + axis->x * sin_theta;
	r.m[2][2] = cos_theta + axis->z * axis->z * (1 - cos_theta);
	return (r);
}

t_vec3	rotate_point(t_vec3 *p, t_vec3 *center, t_matrix3x3 *r)
{
	t_point3	rot_p;
	t_point3	tmp_p;

	tmp_p.x = p->x - center->x;
	tmp_p.y = p->y - center->y;
	tmp_p.z = p->z - center->z;
	rot_p.x = r->m[0][0] * tmp_p.x + r->m[0][1] * tmp_p.y + r->m[0][2]
		* tmp_p.z;
	rot_p.y = r->m[1][0] * tmp_p.x + r->m[1][1] * tmp_p.y + r->m[1][2]
		* tmp_p.z;
	rot_p.z = r->m[2][0] * tmp_p.x + r->m[2][1] * tmp_p.y + r->m[2][2]
		* tmp_p.z;
	rot_p.x += center->x;
	rot_p.y += center->y;
	rot_p.z += center->z;
	return (rot_p);
}

t_point3	calc_center(t_vec3 *dir, t_vec3 *base, double h)
{
	t_ray		ray;
	t_point3	cent;

	ray.dir = *dir;
	ray.orig = *base;
	cent = ray_at(&ray, h);
	return (cent);
}
