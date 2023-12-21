/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:38:42 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/21 17:56:30 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <time.h>

#define U 0
#define V 1
#define W 2

void	render_image(t_scene *scene, int img_w, int img_h)
{
	t_mlx	*data;
	void	*tmp_img_ptr;
	clock_t	t;
	
	t = clock();
	data = &scene->data;
	tmp_img_ptr = data->img.ptr;
	init_mlx_image(data, img_w, img_h);
	set_camera(&scene->camera, img_w, img_h);
	start_raytracer(data, scene, img_w, img_h);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	if (tmp_img_ptr != NULL)
		mlx_destroy_image(data->mlx, tmp_img_ptr);
	t = clock() - t;
	ft_printf("\r Render time: %ims", (int)((double)t / CLOCKS_PER_SEC * 1000));
	draw_menu(scene);
}

void	create_ray(t_camera *camera, t_ray *r, int i, int j)
{
	t_point3	pixel_center;
	t_vec3		tmp_i;
	t_vec3		tmp_j;

	tmp_i = product_vec3_r(&camera->pixel_delta_u, i);
	tmp_j = product_vec3_r(&camera->pixel_delta_v, j);
	pixel_center = add_vec3(&camera->pixel00_loc, &tmp_i);
	pixel_center = add_vec3(&pixel_center, &tmp_j);
	r->orig = camera->center;
	r->dir = substract_vec3(&pixel_center, &camera->center);
}


void	start_raytracer(t_mlx *data, t_scene *scene, int img_w, int img_h)
{
	t_camera	*camera;
	t_ray		r;
	t_color		color;
	int			i;
	int			j;
	
	camera = &scene->camera;
	j = 0;
	while (j < img_h)
	{
		i = 0;
		while (i < img_w)
		{
			create_ray(camera, &r, i, j);
			color = send_ray(&r, scene);
			my_put_pixel(data, i, j, create_color(0, color.x, color.y, color.z));
			i++;
		}
		j++;
	}
}

void	set_camera(t_camera *camera, int img_w, int img_h)
{
	t_vec3	cam_axis[3];
	t_vec3	tmp;

	camera->vup = (t_vec3){0,1,0}; 
	camera->focal_length = 1.0;
	camera->viewport_width = 2 * tan(deg_to_rad(camera->hfov) / 2) * camera->focal_length;
	camera->viewport_height = camera->viewport_width * ((double)img_h/(double)img_w);
	cam_axis[W] = unit_vector(&camera->dir);
	product_vec3(&cam_axis[W], -1);
	tmp = cross(&camera->vup, &cam_axis[W]);
	cam_axis[U] = unit_vector(&tmp);
	cam_axis[V] = cross(&cam_axis[W], &cam_axis[U]);
	camera->viewport_u = product_vec3_r(&cam_axis[U], camera->viewport_width);
	tmp = product_vec3_r(&cam_axis[V], -1);
	camera->viewport_v = product_vec3_r(&tmp, camera->viewport_height);  
	camera->pixel_delta_u = division_vec3_r(&camera->viewport_u, img_w);
	camera->pixel_delta_v = division_vec3_r(&camera->viewport_v, img_h);
	set_pixel00(camera, cam_axis);
}

void	set_pixel00(t_camera *camera, t_vec3 *cam_axis)
{
	t_vec3		half_view[2];
	t_vec3		tmp_focal;
	t_vec3		center_viewport;
	t_point3	viewport_upper_left;
	t_vec3		half_pixel;

	tmp_focal = product_vec3_r(&cam_axis[W], camera->focal_length);
	half_view[U] = division_vec3_r(&camera->viewport_u, 2);
	half_view[V] = division_vec3_r(&camera->viewport_v, 2);
	center_viewport = substract_vec3(&camera->center, &tmp_focal);
	viewport_upper_left = substract_vec3(&center_viewport, &half_view[U]);
	viewport_upper_left = substract_vec3(&viewport_upper_left, &half_view[V]);
	half_pixel = add_vec3(&camera->pixel_delta_u, &camera->pixel_delta_v);
	product_vec3(&half_pixel, 0.5);
	camera->pixel00_loc = add_vec3(&viewport_upper_left, &half_pixel);
}
