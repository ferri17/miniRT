/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:38:42 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/25 11:47:16 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color ray_color(const t_ray *r)
{
	t_vec3	unit_direction = unit_vector(&r->dir);
	double	a = 0.5 * (unit_direction.e[Y] + 1.0);
	printf("%.2f \n", a);
	t_color	color1 = {1.0, 1.0, 1.0};
	product_vec3(&color1, (1.0 - a));
	t_color	color2 = {0.5, 0.7, 1.0};
	product_vec3(&color2, a);
	return (add_vec3(&color1, &color2));
}

void	render_image(t_mlx *data, t_scene *scene)
{
	init_mlx_image(&data, WIN_W, WIN_H);
	set_camera(&scene->camera);
	start_raytracer(data, scene);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

void	start_raytracer(t_mlx *data, t_scene *scene)
{
	j = 0;
	while (j < WIN_H)
	{
		ft_printf("\r Scaning line %i/%i", j + 1, WIN_H);
		i = 0;
		while (i < WIN_W)
		{
			//auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			t_vec3		tmp_i = product_vec3_r(&pixel_delta_u, i);
			t_vec3		tmp_j = product_vec3_r(&pixel_delta_v, j);
			t_point3	pixel_center = add_vec3(&pixel00_loc, &tmp_i);
			pixel_center = add_vec3(&pixel_center, &tmp_j);

            //auto ray_direction = pixel_center - camera_center;
			t_vec3	ray_direction = substract_vec3(&pixel_center, &camera->center);

            //ray r(camera_center, ray_direction);
			t_ray	r;
			r.orig = camera->center;
			r.dir = ray_direction;

            t_color pixl = ray_color(&r);
			int	r1 = pixl.e[X] * 255.999;
			int	g = pixl.e[Y] * 255.999;
			int	b = pixl.e[Z] * 255.999;
			int		color = create_color(0, r1, g, b);

			my_put_pixel(&data, i, j, color);
			i++;
		}
		j++;
	}
}

void	set_camera(t_camera *camera)
{
	t_camera	*camera;

	camera = &scene.camera;
	// Camera
	camera->viewport_height = 2.0;
	camera->focal_length = 1.0;
	camera->viewport_width = camera->viewport_height * ((double)(WIN_W/WIN_H));
	camera->center.e[X] = 0.0;
	camera->center.e[Y] = 0.0;
	camera->center.e[Z] = 0.0;

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
    t_vec3	viewport_u = {camera->viewport_width, 0.0, 0.0};
    t_vec3	viewport_v = {0.0, -camera->viewport_height, 0.0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    t_vec3	pixel_delta_u = division_vec3_r(&viewport_u, WIN_W);
    t_vec3	pixel_delta_v = division_vec3_r(&viewport_v, WIN_H);

    // Calculate the location of the upper left pixel.
	t_vec3		tmp_focal = {0.0, 0.0, camera->focal_length};
	t_vec3		tmp_half_view_u = division_vec3_r(&viewport_u, 2);
	t_vec3		tmp_half_view_v = division_vec3_r(&viewport_v, 2);

	t_vec3		tmp1 = substract_vec3(&camera->center, &tmp_focal);
	t_vec3		tmp2 = substract_vec3(&tmp_half_view_u, &tmp_half_view_v);
	t_point3	viewport_upper_left = substract_vec3(&tmp1, &tmp2);

	t_vec3		tmp3 = add_vec3(&pixel_delta_u, &pixel_delta_v);
	product_vec3(&tmp3, 0.5);
	t_point3	pixel00_loc = add_vec3(&viewport_upper_left, &tmp3);
}
