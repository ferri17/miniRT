/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:17:03 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/09 17:48:13 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <stdio.h>

void	screen_object_center(t_scene *scene)
{
	t_world	pl;
	t_world	*obj;
	t_ray	ray;
	t_vec3	obj_center;
	t_hit	hit_rec;

	obj = scene->selected;
	obj_center = *(obj->get_position_pointer(&obj->type));
	ray.orig = scene->camera.center;
	ray.dir = substract_vec3(&obj_center, &scene->camera.center);
	ray.dir = unit_vector(&ray.dir);
	pl.type.pl = malloc(sizeof(t_plane));
	pl.type.pl->center = scene->camera.pixel00_loc;
	pl.type.pl->normal = unit_vector(&scene->camera.dir); //check if camera dir is already unit vector
	hit_rec.ray_tmin = 0.001;
	hit_rec.ray_tmax = INT_MAX;
	if (pl.hit(&ray, pl.type, &hit_rec))
	{
		t_vec3	inter_pxl00 = substract_vec3(&hit_rec.p, &scene->camera.pixel00_loc);
		double	_x = dot(&inter_pxl00, &scene->camera.viewport_u);
		double	_y = dot(&inter_pxl00, &scene->camera.viewport_v);
		printf("x: %f\ny: %f\n", _x, _y);
	}
}

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
		screen_object_center(scene);
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