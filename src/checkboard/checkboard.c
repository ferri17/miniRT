/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/21 15:26:52 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

double	quit_decimals(double num)
{
	const double	ratio = (num * 5) / 2.0;

	return (ratio - floor(ratio));
}

t_color	checker_color(t_uv uv, t_color color)
{
    double tmp1 = quit_decimals(uv.u);
    double tmp2 = quit_decimals(uv.v);

    if ((tmp1 < 0.5) ^ (tmp2 < 0.5)) {
        return (color); // t_color blanco
    } else {
        return (t_color){0.0f, 0.0f, 0.0f}; // t_color negro
    }
}

t_color	get_color_sphere(t_vec3 *p_hit, t_objects type)
{
	// t_point3 p = substract_vec3(p_hit, &type.sp->center);
	// p = unit_vector(&p);
	// t_color color;
	// double theta = acos(-p.y);
	// double phi = atan2(-p.z, p.x) + M_PI;
	// if (sin(phi * C_FACTOR) * sin(theta * C_FACTOR) > 0)
	// 	color = (t_color){0.0, 0.0, 0.0};
	// else
	// 	color = world->materia.color;
	// return (color);
	t_uv uv = get_spherical_map(p_hit, &type.sp->center, type.sp->radius);
	uv.u *= 4;
	uv.v *= 2;
	return (checker_color(uv, (t_color){255,255,255}));
}

t_color	get_color_plane(t_vec3 *p_hit, t_objects type)
{
	t_uv uv = get_planar_map(p_hit, &type.pl->normal, &type.pl->center);
	return (checker_color(uv, (t_color){255,255,255}));
}

t_color	get_color_cone(t_vec3 *p_hit, t_objects type)
{
	t_color color;
	if (type.cn->hit[H_CONE])
	{
		t_uv uv = get_cylinder_map(p_hit, &type.cn->dir, &type.cn->center, type.cn->height);
		uv.u *= 6;
		uv.v *= 2;
		return (checker_color(uv, (t_color){255,255,255}));
	}
	else
	{
		t_uv uv = get_planar_map(p_hit, &type.cn->dir, &type.pl->center);
		uv.u *= 6;
		uv.v *= 2;
		return (checker_color(uv, (t_color){255,255,255}));
	}
	return (color);
}

t_color	get_color_cylinder(t_vec3 *p_hit, t_objects type)
{
	//t_color color;
	if (type.cy->hit[H_CYLINDER])
	{
		t_uv uv = get_cylinder_map(p_hit, &type.cy->dir, &type.cy->center, type.cy->height);
		uv.u *= 140;
		uv.v *= 40;
		return (checker_color(uv, (t_color){255,255,255}));
	}
	// else
	// {
		// t_uv uv = get_planar_map(p_hit, &type.cy->dir, &type.cy->center);
		// uv.u *= 10;
		// uv.v *= 2;
		// return (checker_color(uv, (t_color){255,255,255}));
	// }
	return ((t_color){255,255,255});
}

