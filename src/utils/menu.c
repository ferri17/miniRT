/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:17:03 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/06 15:16:17 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <stdio.h>

void	draw_menu(t_scene *scene)
{
	t_mlx	*data;
	char	value[100];
	
	if (scene->selected)
	{
		//printf("%f\n", scene->selected->type.sp->center.x);
		data = &scene->data;
		if (sprintf(value, "%.2f", scene->selected->type.sp->center.x) < 0)
			value[0] = '\0';
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - 200, 0, 0xFFFFFF, value);
		if (sprintf(value, "%.2f", scene->selected->type.sp->center.y) < 0)
			value[0] = '\0';
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - 200, 20, 0xFFFFFF, value);
		if (sprintf(value, "%.2f", scene->selected->type.sp->center.z) < 0)
			value[0] = '\0';
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - 200, 40, 0xFFFFFF, value);
		//mlx_string_put(data->mlx, data->mlx_win, 0, 50, 0xFFFFFF, ft_itoa(y));
		//mlx_string_put(data->mlx, data->mlx_win, 0, 100, 0xFFFFFF, ft_itoa(z));
		//screen_object_center(scene, &center);
	}
}
/* void	screen_object_center(t_scene *scene, t_vec3	*point)
{
	t_plane	pl;
	t_vec3	tmp;
	double	denom;
	double	t;
	double	d;
	
	pl.center = *point;
	tmp = add_vec3(&scene->camera.pixel00_loc, &scene->camera.viewport_u);
	pl.normal = cross(&scene->camera.pixel00_loc, &tmp);

	t_ray	r;
	r.orig = scene->camera.center;
	r.dir = substract_vec3(&point, &scene->camera.center);

	denom = dot(&pl.normal, &r.dir);
	//if (fabs(denom) < 1e-8)
	//	return false;
	d = dot(&pl.normal, &pl.center);
	t = (d - dot(&pl.normal, &r.orig)) / denom;
	//if (t <= rec->ray_tmin || t >= rec->ray_tmax)
	//	return (false);
	t_point3	hit;
	hit = ray_at(&r, t);
	int	pixel_x = division_vec3
	return (true);
} */