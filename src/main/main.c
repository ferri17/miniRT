/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/24 11:46:08 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <stdio.h>

void print_shit(t_scene scene)
{
	printf("-----CAMERA-----\n");
	printf("Coord: x:%f y:%f z:%f\n", scene.camera.center.e[X], scene.camera.center.e[Y], scene.camera.center.e[Z]);
	printf("Direct: x:%f y:%f z:%f\n", scene.camera.dir.e[X], scene.camera.dir.e[Y], scene.camera.dir.e[Z]);
	printf("FOV: %d\n", scene.camera.hfov);
	printf("-----AMBIENT-----\n");
	printf("COLOR: R:%f G:%f B:%f\n", scene.ambligth.color.e[R], scene.ambligth.color.e[G], scene.ambligth.color.e[B]);
	printf("RATIO: %f\n", scene.ambligth.ratio);
	printf("-----LIGTH-----\n");
	printf("Coord: x:%f y:%f z:%f\n", scene.ligth.center.e[X], scene.ligth.center.e[Y], scene.ligth.center.e[Z]);
	printf("COLOR: R:%f G:%f B:%f\n", scene.ligth.color.e[R], scene.ligth.color.e[G], scene.ligth.color.e[B]);
	printf("BRIGT: %f\n", scene.ligth.brigt);
	while (scene.objs)
	{
		ft_printf("-----OBJS-----\n");
		scene.objs->hit(scene.objs->type);
		scene.objs = scene.objs->next;
	}
}

t_color ray_color(const t_ray *r)
{
	t_vec3	unit_direction = unit_vector(&r->dir);
	printf("%.2f,%.2f,%.2f \n", unit_direction.e[X], unit_direction.e[Y], unit_direction.e[Z]);
	double	a = 0.5 * (unit_direction.e[Y] + 1.0);
	t_color	color1 = {1.0, 1.0, 1.0};
	product_vec3(&color1, (1.0 - a));
	t_color	color2 = {0.5, 0.7, 1.0};
	//product_vec3(&color1, a);
	return (add_vec3(&color1, &color2));
	//t_color tmp = add_vec3(&color1, &color2);
	//printf("%f,%f,%f \n", tmp.e[X], tmp.e[Y], tmp.e[Z]);
    //return (add_vec3(&color1, &color2));

	/* vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); */
}


int	main(int argc, char **argv)
{
	int	i;
	int	j;
	t_scene	scene;
	t_mlx	data;

	if (check_args(argc, argv) == 1)
		return (1);
	scene = init_structs();
	if (init_map(argv[1], &scene))
	{
		print_shit(scene);
		ft_printf_fd(STDERR_FILENO, ERR_INVALID_MAP);
		return (1);
	}
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "MINIRT");
	init_image(&data);

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
			int		color = create_color(0, pixl.e[R], pixl.e[R], pixl.e[R]);

			my_put_pixel(&data, i, j, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img.ptr, 0, 0);
	mlx_hook(data.mlx_win, KEYDOWN, 0, key_down, (void *)&data);
	mlx_hook(data.mlx_win, DESTROY, 0, close_program, (void *)&data);
	mlx_loop(data.mlx);
	//print_shit(scene);

	//data.mlx = mlx_init();
	//data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "MINIRT");
	//mlx_hook(data.mlx_win, KEYDOWN, 0, key_down, (void *)&data);
	//mlx_loop(data.mlx);
	return (0);
}
