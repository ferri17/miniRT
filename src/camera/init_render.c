/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:38:42 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/27 01:27:52 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color ray_color(const t_ray *r, t_scene *scene)
{
	t_world	*objs;

	objs = scene->objs;
	if (objs->hit(r, objs->type))
	{
		t_color	hit = {1.0, 0.0, 0.0};
		return (hit);
	}
	t_vec3	unit_direction = unit_vector(&r->dir);
	double	a = 0.5 * (unit_direction.e[Y] + 1.0);
	t_color	color1 = {1.0, 1.0, 1.0};
	product_vec3(&color1, (1.0 - a));
	t_color	color2 = {0.5, 0.7, 1.0};
	product_vec3(&color2, a);
	return (add_vec3(&color1, &color2));
}

void	render_image(t_scene *scene, int img_w, int img_h)
{
	t_mlx	*data;

	data = &scene->data;
	init_mlx_image(data, img_w, img_h);
	set_camera(&scene->camera, img_w, img_h);
	start_raytracer(data, scene, img_w, img_h);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

void	start_raytracer(t_mlx *data, t_scene *scene, int img_w, int img_h)
{
	t_camera	*camera;
	int	i;
	int	j;
	
	camera = &scene->camera;
	j = 0;
	while (j < img_h)
	{
		ft_printf("\r Scaning line %i/%i", j + 1, WIN_H);
		i = 0;
		while (i < img_w)
		{
			//auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			t_vec3		tmp_i = product_vec3_r(&camera->pixel_delta_u, i);
			t_vec3		tmp_j = product_vec3_r(&camera->pixel_delta_v, j);
			t_point3	pixel_center = add_vec3(&camera->pixel00_loc, &tmp_i);
			pixel_center = add_vec3(&pixel_center, &tmp_j);

            //auto ray_direction = pixel_center - camera_center;
			t_vec3	ray_direction = substract_vec3(&pixel_center, &camera->center);

            //ray r(camera_center, ray_direction);
			t_ray	r;
			r.orig = camera->center;
			r.dir = ray_direction;
	
            t_color pixl = ray_color(&r, scene);
			int	red = pixl.e[X] * 255.999;
			int	green = pixl.e[Y] * 255.999;
			int	blue = pixl.e[Z] * 255.999;
			int		color = create_color(0, red, green, blue);

			my_put_pixel(data, i, j, color);
			i++;
		}
		j++;
	}
}

void	set_camera(t_camera *camera, int img_w, int img_h)
{
	// Camera
	camera->viewport_height = 2.0;
	camera->focal_length = 1.0;
	camera->viewport_width = camera->viewport_height * ((double)(img_w/img_h));

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
    camera->viewport_u = (t_vec3){camera->viewport_width, 0.0, 0.0};
    camera->viewport_v = (t_vec3){0.0, -camera->viewport_height, 0.0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    camera->pixel_delta_u = division_vec3_r(&camera->viewport_u, img_w);
    camera->pixel_delta_v = division_vec3_r(&camera->viewport_v, img_h);

    // Calculate the location of the upper left pixel.
	t_vec3		tmp_focal = {0.0, 0.0, camera->focal_length};
	t_vec3		half_view_u = division_vec3_r(&camera->viewport_u, 2);
	t_vec3		half_view_v = division_vec3_r(&camera->viewport_v, 2);

	t_vec3		center_viewport = substract_vec3(&camera->center, &tmp_focal);
	t_vec3		tmp = substract_vec3(&center_viewport, &half_view_u);
	t_point3	viewport_upper_left = substract_vec3(&tmp, &half_view_v);

	t_vec3		half_pixel = add_vec3(&camera->pixel_delta_u, &camera->pixel_delta_v);
	product_vec3(&half_pixel, 0.5);
	camera->pixel00_loc = add_vec3(&viewport_upper_left, &half_pixel);
}

