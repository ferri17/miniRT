/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/18 19:31:59 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

double	ft_residual(double num)
{
	const double	ratio = (num + 1) / 1 / 2.0;

	return (ratio - floor(ratio));
}

void	ft_rotate(double *rot_u, double *rot_v, double u, double v)
{
	const double	cos_a = cos(34);
	const double	sin_a = sin(34);
	double			aux[2];

	aux[0] = u * cos_a - v * sin_a;
	aux[1] = u * sin_a + v * cos_a;
	*rot_u = aux[0];
	*rot_v = aux[1];
}

int	ft_tile(double u, double v)
{
	double			residual[2];
	double			rot_u;
	double			rot_v;

	ft_rotate(&rot_u, &rot_v, u, v);
	residual[0] = ft_residual(rot_u);
	residual[1] = ft_residual(rot_v);
	return ((residual[0] < 0.5) ^ (residual[1] < 0.5));
}

t_color	pattern_at(double u, double v, t_color color)
{
	double u2 = floor(u * 10);
	double v2 = floor(v * 10);
	double	test = (u2 + v2); 
	if (fmod(test, 2) == 0)
		return ((t_color){0, 0, 0});
	else
		return (color);
}

t_color	get_color_sphere(t_vec3 p_hit, t_world *world)
{
	t_point3 p = substract_vec3(&p_hit, &world->type.sp->center);
	p = unit_vector(&p);
	t_color color;
	double theta = acos(-p.y);
	double phi = atan2(-p.z, p.x) + M_PI;
	if (sin(phi * C_FACTOR) * sin(theta * C_FACTOR) > 0)
		color = (t_color){0.0, 0.0, 0.0};
	else
		color = world->materia.color;
	return (color);
}

t_color	get_color_plane(t_vec3 p_hit, t_world *world)
{
	double u = 0.5 + dot(&world->type.pl->normal, &p_hit) / 2.0;
	double v = 0.5 - asin(world->type.pl->normal.y) / M_PI;


	// Realiza el mapeo a cuadros alternados

	// Aplica el patrón a cuadros
	if (fmod(u + v, 2) == 0)
		return ((t_color){0, 0, 0});
	else
		return (world->materia.color);
}

t_color	get_color_cone(t_vec3 p_hit, t_world *world)
{
	//return (checkboard(p_hit));
	t_color color;
	if (world->type.cn->hit[H_CONE])
	{
		t_point3 p = substract_vec3(&p_hit, &world->type.cn->center);
		p = unit_vector(&p);
		double theta = acos(-p.y);
		double phi = atan2(-p.z, p.x) + M_PI;
		if (sin(phi * C_FACTOR) * sin(theta * C_FACTOR) > 0)
			color = (t_color){0.0, 0.0, 0.0};
		else
			color = world->materia.color;
	}
	else
	{
		double u = fmod(p_hit.x, 1.0);
		double v = fmod(p_hit.y, 1.0);
		
		return (pattern_at(u, v, world->materia.color));
	}
	return (color);
}

double	ft_limit_cyl_height(double height, const t_cylinder *cy)
{
	const double	min_height = -0.999 * cy->height;
	const double	max_height = 0.999 * cy->height;

	if (height < min_height)
		return (min_height);
	if (height > max_height)
		return (max_height);
	return (height);
}

t_color	get_color_cylinder(t_vec3 p_hit, t_world *world)
{
	//return (checkboard(p_hit));
	t_color color;

	if (world->type.cy->hit[H_CYLINDER])
	{
		t_vec3	trash;
		double	x;
		double	y;
		t_ray		displace;
		t_point3	test;
		double	u;
		double	v;

		test = ray_at(&displace, world->type.cy->height);

		displace.orig = world->type.cy->center;
		displace.dir = world->type.cy->dir;
		trash = substract_vec3(&p_hit, &world->type.cy->center);
		x = dot(&world->type.cy->center, &trash);
		y = dot(&test, &trash);
		v = dot(&world->type.cy->dir, &trash);
		v = ft_limit_cyl_height(v, world->type.cy);
		u = 1 - ((atan2(x, y) / (M_PI * 2)) + 0.5);
		if (ft_tile(u, v))
			return ((t_color){0,0,0});
		return (world->materia.color);
	}
	else
	{
		double u = fmod(p_hit.x, 1.0);
		double v = fmod(p_hit.y, 1.0);
		
		return (pattern_at(u, v, world->materia.color));
	}
	return (color);
}

