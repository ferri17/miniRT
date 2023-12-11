/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:17:03 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/11 02:51:47 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <stdio.h>

bool	hit_plane2(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_plane	*pl;
	double	denom;
	double	t;
	double	d;
	
	pl = obj.pl;
	denom = dot(&pl->normal, &ray->dir);
	if (fabs(denom) < 1e-8)
		return false;
	d = dot(&pl->normal, &pl->center);
	t = (d - dot(&pl->normal, &ray->orig)) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = pl->normal;
	return (true);
}

void	screen_object_center(t_scene *scene, double coord[2])
{
	t_world	*pl = malloc(sizeof(t_world));
	t_world	*obj;
	t_ray	ray;
	t_vec3	obj_center;
	t_hit	hit_rec;

	t_vec3	inter_pxl00;
	t_vec3	tmp_u;
	t_vec3	tmp_v;

	obj = scene->selected;
	obj_center = *(obj->get_position_pointer(&obj->type));
	ray.orig = scene->camera.center;
	ray.dir = substract_vec3(&obj_center, &scene->camera.center);
	ray.dir = unit_vector(&ray.dir);
	pl->type.pl = malloc(sizeof(t_plane));
	pl->type.pl->center = scene->camera.pixel00_loc;
	pl->type.pl->normal = product_vec3_r(&scene->camera.dir, -1); // IF ERROR CHECK IF CAMERA.DIR IS A UNIT VECTOR
	hit_rec.ray_tmin = 0.0;
	hit_rec.ray_tmax = INT_MAX;
	/* if (pl->hit(&ray, pl->type, &hit_rec))   //CRASH
		ft_printf("Das\n"); */
	if (hit_plane2(&ray, pl->type, &hit_rec))
	{
		inter_pxl00 = substract_vec3(&hit_rec.p, &scene->camera.pixel00_loc);

		tmp_u = unit_vector(&scene->camera.viewport_u);
		tmp_v = unit_vector(&scene->camera.viewport_v);
		coord[X] = dot(&inter_pxl00, &tmp_u);
		coord[Y] = dot(&inter_pxl00, &tmp_v);
		coord[X] = coord[X] / scene->camera.viewport_width * WIN_W;
		coord[Y] = coord[Y] / scene->camera.viewport_height * WIN_H;
	}
	coord = NULL;
}

void	draw_menu(t_scene *scene)
{
	t_mlx	*data;
	double	coord[2];
	char	value[100];
	
	if (scene->selected)
	{
		screen_object_center(scene, coord);
		if ((double *)coord == NULL)         //CHECK IF ITS OKAY
			return ;
		data = &scene->data;
		if (sprintf(value, "x[%.2f]", scene->selected->type.sp->center.x) < 0)
			value[0] = '\0';
		mlx_string_put(data->mlx, data->mlx_win, (int)coord[X] - 40, (int)coord[Y] - 20, 0xFFFFFF, value);
		if (sprintf(value, "y[%.2f]", scene->selected->type.sp->center.y) < 0)
			value[0] = '\0';
		mlx_string_put(data->mlx, data->mlx_win, (int)coord[X] - 40, (int)coord[Y], 0xFFFFFF, value);
		if (sprintf(value, "z[%.2f]", scene->selected->type.sp->center.z) < 0)
			value[0] = '\0';
		mlx_string_put(data->mlx, data->mlx_win, (int)coord[X] - 40, (int)coord[Y] + 20, 0xFFFFFF, value);
	}
	//if (scene->render_mode == EDIT_MODE)
	//	return ;
		//mlx_string_put(data->mlx, data->mlx_win, (int)coord[X] - 40, (int)coord[Y] + 20, 0xFFFFFF, value);
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