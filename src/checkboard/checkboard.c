/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/14 14:48:59 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	checkboard(t_vec3 p_hit)
{
	t_point3	coords;
	t_point3	val;
	int			party_mix;

	coords.x = abs((int)floor(p_hit.x * 10));
	coords.y = abs((int)floor(p_hit.y * 10));
	coords.z = abs((int)floor(p_hit.z * 10));
	val.x = (int)coords.x % 2;
	val.y = (int)coords.y % 2;
	val.z = (int)coords.z % 2;
	party_mix = ((int)val.x ^ (int)val.y) ^ (int)val.z;
	if (party_mix) {
		return (t_color){0.0, 0.0, 0.0};
	} else {
		return (t_color){255, 255, 255};
	}
}

t_color	get_color_sphere(t_vec3 p_hit, t_world *world)
{
	return (checkboard(p_hit));
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
	return (checkboard(p_hit));
	int xInteger = (int)(floor(C_FACTOR * p_hit.x + 1e-6));
	int yInteger = (int)(floor(C_FACTOR * p_hit.y + 1e-6));
	int zInteger = (int)(floor(C_FACTOR * p_hit.z + 1e-6));

	bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

	if (isEven) {
		return (t_color){0.0, 0.0, 0.0};
	} else {
		return world->materia.color;
	}
}

t_color	get_color_cone(t_vec3 p_hit, t_world *world)
{
	return (checkboard(p_hit));
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
		int xInteger = (int)(floor(C_FACTOR * p_hit.x + 1e-8));
		int yInteger = (int)(floor(C_FACTOR * p_hit.y + 1e-8));
		int zInteger = (int)(floor(C_FACTOR * p_hit.z + 1e-8));

		bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

		if (isEven) {
			return (t_color){0.0, 0.0, 0.0};
		} else {
			return world->materia.color;
		}
	}
	return (color);
}

t_color	get_color_cylinder(t_vec3 p_hit, t_world *world)
{
	return (checkboard(p_hit));
	t_color color;

	if (world->type.cy->hit[H_CYLINDER])
	{
	t_point3 p = substract_vec3(&p_hit, &world->type.cy->center);
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
		int xInteger = (int)(floor(C_FACTOR * p_hit.x + 1e-8));
		int yInteger = (int)(floor(C_FACTOR * p_hit.y + 1e-8));
		int zInteger = (int)(floor(C_FACTOR * p_hit.z + 1e-8));

		bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

		if (isEven) {
			return (t_color){0.0, 0.0, 0.0};
		} else {
			return world->materia.color;
		}
	}
	return (color);
}

