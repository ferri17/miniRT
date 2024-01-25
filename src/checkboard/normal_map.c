/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:15:12 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/25 19:26:56 by fbosch           ###   ########.fr       */
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
	color = map_uv_to_color(&uv, &obj->materia.bump);
	return (color);
}
/* 
color = (t_color){0,0,0};
	uv = get_spherical_map(p_hit, &objs->type.sp->center,
		objs->type.sp->radius);
	if (objs->materia.texture == BITMAP || objs->materia.texture == BITMAP_BUMPMAP)
		color = map_uv_to_color(&uv, &objs->materia); */
