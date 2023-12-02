/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:38:42 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/01 23:45:24 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

#define U 0
#define V 1
#define W 2

t_color	send_ray(const t_ray *r, t_scene *scene)
{
	t_color	hit;
	t_hit	tmp_hit;
	t_world	*objs;
	bool	any_hit = false;
	
	tmp_hit.ray_tmin = 0;
	tmp_hit.ray_tmax = INT_MAX;
	objs = scene->objs;
	while (objs)
	{
		if (objs->hit(r, objs->type, &tmp_hit))
		{
			tmp_hit.ray_tmax = tmp_hit.t;
			//t_vec3 unit = unit_vector(&tmp_hit.normal);
			//t_vec3 unit = unit_vector(&objs->color);

			
			t_vec3 tmp1 = product_vec3_r(&r->dir, -1);
			t_vec3 tmp2 = unit_vector(&tmp1);
			double	a = dot(&tmp2, &tmp_hit.normal);
			clamp_number(a, 0, 1);

			hit = (t_color){a, a, a};
			any_hit = true;
		}
		objs = objs->next;
	}
	if (any_hit)
		return (hit);
	/* BACKGROUND */
	t_vec3	unit_direction = unit_vector(&r->dir);
	double	a = 0.5 * (unit_direction.y + 1.0);
	t_color	color1 = {1.0, 1.0, 1.0};
	product_vec3(&color1, (1.0 - a));
	t_color	color2 = {0.5, 0.7, 1.0};
	product_vec3(&color2, a);
	return (add_vec3(&color1, &color2));
	/* BACKGROUND */
}

#include <time.h>

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
}

void	start_raytracer(t_mlx *data, t_scene *scene, int img_w, int img_h)
{
	t_camera	*camera;
	t_vec3		tmp_i;
	t_vec3		tmp_j;
	t_vec3		ray_direction;
	t_point3	pixel_center;
	t_ray	r;
	t_color pixel;
	int	red;
	int	green;
	int	blue;
	int	color;
	int	i;
	int	j;
	
	camera = &scene->camera;
	j = 0;
	while (j < img_h)
	{
		//ft_printf("\r Scaning line %i/%i", j + 1, WIN_H);
		i = 0;
		while (i < img_w)
		{
			//auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			tmp_i = product_vec3_r(&camera->pixel_delta_u, i);
			tmp_j = product_vec3_r(&camera->pixel_delta_v, j);
			pixel_center = add_vec3(&camera->pixel00_loc, &tmp_i);
			pixel_center = add_vec3(&pixel_center, &tmp_j);

            //auto ray_direction = pixel_center - camera_center;
			ray_direction = substract_vec3(&pixel_center, &camera->center);

            //ray r(camera_center, ray_direction);
			r.orig = camera->center;
			r.dir = ray_direction;
	
            pixel = send_ray(&r, scene);
			red = pixel.x * 255.999;
			green = pixel.y * 255.999;
			blue = pixel.z * 255.999;
			color = create_color(0, red, green, blue);

			my_put_pixel(data, i, j, color);
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
