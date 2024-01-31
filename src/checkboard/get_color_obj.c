/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/31 13:59:29 by apriego-         ###   ########.fr       */
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
		return ((t_color){0, 0, 0});
	b = (unsigned char)img_tex->info[i + 0];
	g = (unsigned char)img_tex->info[i + 1];
	r = (unsigned char)img_tex->info[i + 2];
	color.x = (double)r / 255.999;
	color.y = (double)g / 255.999;
	color.z = (double)b / 255.999;
	return (color);
}

t_color	get_color_sphere(t_vec3 *p_hit, t_world *objs, t_texture type)
{
	t_uv	uv;
	t_color	color;

	if (type == DEFAULT && objs->materia.texture != CHECKBOARD)
		return (objs->materia.color);
	color = (t_color){0, 0, 0};
	uv = get_spherical_map(p_hit, &objs->type.sp->center,
			objs->type.sp->radius);
	if (type == BITMAP)
		color = map_uv_to_color(&uv, &objs->materia.bit);
	else if (objs->materia.texture == CHECKBOARD)
	{
		uv.u *= 4;
		uv.v *= 2;
		color = checker_color(uv, objs->materia.color);
	}
	else
	{
		return (objs->materia.color);
	}
	return (color);
}

t_color	get_color_plane(t_vec3 *p_hit, t_world *objs, t_texture type)
{
	t_uv	uv;
	t_color	color;

	if (type == DEFAULT && objs->materia.texture != CHECKBOARD)
		return (objs->materia.color);
	color = (t_color){0, 0, 0};
	uv = get_planar_map(p_hit, &objs->type.pl->normal, &objs->type.pl->center);
	if (type == BITMAP)
	{
		uv.u = uv.u - floor(uv.u);
		uv.v = uv.v - floor(uv.v);
		color = map_uv_to_color(&uv, &objs->materia.bit);
	}
	else if (objs->materia.texture == CHECKBOARD)
		color = checker_color(uv, objs->materia.color);
	else
	{
		return (objs->materia.color);
	}
	return (color);
}

t_color	get_color_cone(t_vec3 *p_hit, t_world *objs, t_texture type)
{
	t_point3	cent;
	t_ray		ray;
	t_color		color;

	if (type == DEFAULT && objs->materia.texture != CHECKBOARD)
		return (objs->materia.color);
	ray.dir = objs->type.cn->dir;
	ray.orig = objs->type.cn->center;
	cent = ray_at(&ray, objs->type.cn->height / 2);
	if (objs->materia.texture == CHECKBOARD)
		color = get_cn_chess(p_hit, objs, &cent, &ray);
	else if (type == BUMPMAP)
		color = get_cn_bit(p_hit, objs, &cent, &ray);
	else
	{
		return (objs->materia.color);
	}
	return (color);
}

t_color	get_color_cylinder(t_vec3 *p_hit, t_world *objs, t_texture type)
{
	t_point3	cent;
	t_ray		ray;
	t_color		color;

	if (type == DEFAULT && objs->materia.texture != CHECKBOARD)
		return (objs->materia.color);
	ray.dir = objs->type.cy->dir;
	ray.orig = objs->type.cy->center;
	cent = ray_at(&ray, objs->type.cy->height / 2);
	if (objs->materia.texture == CHECKBOARD)
		color = get_cy_chess(p_hit, objs, &cent, &ray);
	else if (type == BUMPMAP)
		color = get_cy_bit(p_hit, objs, &cent, &ray);
	else
	{
		return (objs->materia.color);
	}
	return (color);
}
