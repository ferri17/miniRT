/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/22 13:06:32 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <stdio.h>

int	close_program(t_mlx *data, int exit_code)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	exit(exit_code);
}

int	key_down(int key, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (key == ESC_KEY)
		close_program(data, EXIT_SUCCESS);
	return (0);
}

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
	while (scene.ligth)
	{
		printf("Coord: x:%f y:%f z:%f\n", scene.ligth->center.e[X], scene.ligth->center.e[Y], scene.ligth->center.e[Z]);
		printf("COLOR: R:%f G:%f B:%f\n", scene.ligth->color.e[R], scene.ligth->color.e[G], scene.ligth->color.e[B]);
		printf("BRIGT: %f\n", scene.ligth->brigt);
		scene.ligth = scene.ligth->next;
	}
	while (scene.objs)
	{
		ft_printf("-----OBJS-----\n");
		scene.objs->hit(scene.objs->type);
		scene.objs = scene.objs->next;
	}
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
	print_shit(scene);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "MINIRT");
	init_image(&data);
	i = 0;
	while (i < WIN_H)
	{
		ft_printf("\r Scaning line %i/%i", i + 1, WIN_H);
		j = 0;
		while (j < WIN_W)
		{
			if (j % 2)
				my_put_pixel(&data, j, i, 0xFF0000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img.ptr, 0, 0);
	mlx_hook(data.mlx_win, KEYDOWN, 0, key_down, (void *)&data);
	mlx_loop(data.mlx);

	//data.mlx = mlx_init();
	//data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "MINIRT");
	//mlx_loop(data.mlx);
	return (0);
}
