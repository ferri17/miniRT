/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/19 01:06:40 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	checker_color(t_uv uv, t_color color)
{
    int square = ((int)(uv.u * 2) + (int)(uv.v * 2)) % 2;
    
    if (square == 0) {
        return (t_color){255, 255, 255}; // t_color blanco
    } else {
        return (t_color){0.0f, 0.0f, 0.0f}; // t_color negro
    }
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
	t_uv uv = get_planar_map(p_hit);
	return (checker_color(uv, world->materia.color));
}

t_color	get_color_cone(t_vec3 p_hit, t_world *world)
{
	t_color color;
	if (world->type.cn->hit[H_CONE])
	{
		t_uv uv = get_cone_map(p_hit);
		uv.u *= 80;
		uv.v *= 6;
		return (checker_color(uv, world->materia.color));
	}
	else
	{
		t_uv uv = get_planar_map(p_hit);
		return (checker_color(uv, world->materia.color));
	}
	return (color);
}

t_color	get_color_cylinder(t_vec3 p_hit, t_world *world)
{
	t_color color;

	if (world->type.cy->hit[H_CYLINDER])
	{
		t_uv uv = get_cylinder_map(p_hit);
		uv.u *= 80;
		uv.v *= 6;
		return (checker_color(uv, world->materia.color));
	}
	else
	{
		t_uv uv = get_planar_map(p_hit);
		return (checker_color(uv, world->materia.color));
	}
	return (color);
}

