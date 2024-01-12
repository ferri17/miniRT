/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:17:03 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/12 13:48:41 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

/* void	world_to_viewport_coord(t_scene *scene, double coord[2], t_point3 *p)
{
	t_vec3	inter_pxl00;
	t_vec3	tmp_u;
	t_vec3	tmp_v;

	inter_pxl00 = substract_vec3(p, &scene->camera.pixel00_loc);
	tmp_u = unit_vector(&scene->camera.viewport_u);
	tmp_v = unit_vector(&scene->camera.viewport_v);
	coord[X] = dot(&inter_pxl00, &tmp_u);
	coord[Y] = dot(&inter_pxl00, &tmp_v);
	coord[X] = coord[X] / scene->camera.viewport_width * WIN_W;
	coord[Y] = coord[Y] / scene->camera.viewport_height * WIN_H;
}

int	screen_object_center(t_scene *scene, double coord[2])
{
	t_world	pl;
	t_plane	tmp;
	t_ray	ray;
	t_vec3	center;
	t_hit	hit_rec;

	center = *(scene->selected->get_position_pointer(&scene->selected->type));
	ray.orig = scene->camera.center;
	ray.dir = substract_vec3(&center, &scene->camera.center);
	ray.dir = unit_vector(&ray.dir);
	pl.type.pl = &tmp;
	pl.type.pl->center = scene->camera.pixel00_loc;
	pl.type.pl->normal = product_vec3_r(&scene->camera.dir, -1); // IF ERROR CHECK IF CAMERA.DIR IS A UNIT VECTOR
	pl.hit = hit_plane;
	hit_rec.ray_tmin = 0.0;
	hit_rec.ray_tmax = INT_MAX;
	if (pl.hit(&ray, pl.type, &hit_rec))
		return (world_to_viewport_coord(scene, coord, &hit_rec.p), 0);
	return (1);
} */

void	draw_selected_object(t_scene *scene)
{
	t_vec3	*center;
	char	value[100];
	
	center = scene->selected->get_position_pointer(&scene->selected->type);
	sprintf(value, "P(%.2f,%.2f,%.2f)", center->x, center->y, center->z);
	my_string_put(&scene->data, WIN_W - XL_PAD * 2, WIN_H - MD_PAD, value);
}

void	draw_menu(t_scene *scene)
{
	t_mlx	*data;
	char	fov[100];

	data = &scene->data;
	if (scene->selected)
		draw_selected_object(scene);
	if (scene->render_mode == EDIT_MODE)
		my_string_put(data, WIN_W - MD_PAD * 3, SM_PAD / 2, "[EDIT MODE]");
	else
		my_string_put(data, WIN_W - MD_PAD * 3, SM_PAD / 2, "[RENDER MODE]");
	draw_slider(data->mlx, data->mlx_win, &scene->slider, WIN_W / 2, WIN_H - MD_PAD);
	sprintf(fov, "Fov = %d", scene->camera.hfov);
	my_string_put(data, WIN_W / 2 - SM_PAD, WIN_H - SM_PAD * 3, fov);
}
