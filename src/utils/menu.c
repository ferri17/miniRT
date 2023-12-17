/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:17:03 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/17 03:14:29 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <stdio.h>

typedef struct s_slider
{
	uint8_t	length;
	int		min_value;
	int		max_value;
	int		*status;
}	t_slider;

t_slider	init_slider(uint8_t length)
{
	t_slider	slider;

	slider.length = length;
	slider.min_value = 1;
	slider.max_value = 179;
	return (slider);
}

int	get_status_relative_increment(t_slider *slider)
{
	int		slider_range;
	float	ratio;

	slider_range = slider->max_value - slider->min_value;
	ratio = (float)(slider_range) / (float)slider->length;
	return (*(slider->status) / ratio);
}

#define SPACE 10

void	draw_slider(void *mlx_ptr, void *mlx_win, t_slider *slider, int x, int y)
{
	int	i;
	int				start;
	int				status_inc;

	start = x - (slider->length * SPACE / 2);
	status_inc = get_status_relative_increment(slider);
	i = 0;
	while (i < slider->length)
	{
		if (i < status_inc)
			mlx_string_put(mlx_ptr, mlx_win, start + (i * SPACE), y, WHITE, "|");
		else
			mlx_string_put(mlx_ptr, mlx_win, start + (i * SPACE), y, WHITE, "-");
		i++;
	}
	mlx_string_put(mlx_ptr, mlx_win, start + (status_inc * SPACE), y, WHITE, "O");
}

void	my_string_put(t_mlx *data, int x, int y, char *txt)
{
	mlx_string_put(data->mlx, data->mlx_win, x, y, WHITE, txt);
}

void	world_to_viewport_coord(t_scene *scene, double coord[2], t_point3 *p)
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
}

void	draw_menu(t_scene *scene) //SPRINTF
{
	t_mlx	*data;
	double	coord[2];
	int		pxl[2];
	char	value[100];

	data = &scene->data;
	if (scene->selected)
	{
		if (screen_object_center(scene, coord) == 0)
		{
			pxl[X] = (int)coord[X];
			pxl[Y] = (int)coord[Y];
			sprintf(value, "x[%.2f]", scene->selected->type.sp->center.x);
			my_string_put(data, pxl[X] - MD_PAD, pxl[Y] - SM_PAD, value);
			sprintf(value, "y[%.2f]", scene->selected->type.sp->center.y);
			my_string_put(data, pxl[X] - MD_PAD, pxl[Y], value);
			sprintf(value, "z[%.2f]", scene->selected->type.sp->center.z);
			my_string_put(data, pxl[X] - MD_PAD, pxl[Y] + SM_PAD, value);
		}
	}
	if (scene->render_mode == EDIT_MODE)
		my_string_put(data, WIN_W - MD_PAD * 3, SM_PAD / 2, "[EDIT MODE]");
	else
		my_string_put(data, WIN_W - MD_PAD * 3, SM_PAD / 2, "[RENDER MODE]");

	sprintf(value, "x[%.4f]", scene->light->center.x);
	my_string_put(data, WIN_W - MD_PAD * 3, WIN_H - MD_PAD * 3, value);
	sprintf(value, "y[%.4f]", scene->light->center.y);
	my_string_put(data, WIN_W - MD_PAD * 3, MD_PAD * 4, value);
	sprintf(value, "z[%.4f]", scene->light->center.z);
	my_string_put(data, WIN_W - MD_PAD * 3, MD_PAD * 5, value);



	t_slider	slider;
	int			status = 90;

	slider = init_slider(50);
	slider.status = &status;
	draw_slider(data->mlx, data->mlx_win, &slider, WIN_W / 2, WIN_H - MD_PAD);
}
