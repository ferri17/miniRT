/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:15:12 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/31 16:59:45 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	get_normal_map_sphere(t_vec3 *p_hit, t_world *obj)
{
	t_uv	uv;
	t_color	color;

	color = (t_color){0,0,0};
	uv = get_spherical_map(p_hit, &obj->type.sp->center,
		obj->type.sp->radius);
	color = map_uv_to_color(&uv, obj->materia.bump);
	return (color);
}

t_color	get_normal_map_plane(t_vec3 *p_hit, t_world *obj)
{
	t_uv	uv;
	t_color	color;

	color = (t_color){0,0,0};
	uv = get_planar_map(p_hit, &obj->type.pl->normal, &obj->type.pl->center);
	uv.u = uv.u - floor(uv.u);
	uv.v = uv.v - floor(uv.v);
	color = map_uv_to_color(&uv, obj->materia.bump);
	return (color);
}

/* 
color = (t_color){0,0,0};
	uv = get_spherical_map(p_hit, &objs->type.sp->center,
		objs->type.sp->radius);
	if (objs->materia.texture == BITMAP || objs->materia.texture == BITMAP_BUMPMAP)
		color = map_uv_to_color(&uv, &objs->materia); */
