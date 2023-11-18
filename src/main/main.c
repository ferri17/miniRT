/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/16 13:48:34 by apriego-         ###   ########.fr       */
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
	printf("Coord: x:%f y:%f z:%f\n", scene.camera.coord.e[X], scene.camera.coord.e[Y], scene.camera.coord.e[Z]);
	printf("Direct: x:%f y:%f z:%f\n", scene.camera.direct.e[X], scene.camera.direct.e[Y], scene.camera.direct.e[Z]);
	printf("FOV: %d\n", scene.camera.fov);
	printf("-----AMBIENT-----\n");
	printf("COLOR: R:%f G:%f B:%f\n", scene.ambligth.color.e[R], scene.ambligth.color.e[G], scene.ambligth.color.e[B]);
	printf("RATIO: %f\n", scene.ambligth.ratio);
	printf("-----LIGTH-----\n");
	printf("Coord: x:%f y:%f z:%f\n", scene.ligth.coord.e[X], scene.ligth.coord.e[Y], scene.ligth.coord.e[Z]);
	printf("COLOR: R:%f G:%f B:%f\n", scene.ligth.color.e[R], scene.ligth.color.e[G], scene.ligth.color.e[B]);
	printf("BRIGT: %f\n", scene.ligth.brigt);
	while (scene.objs)
	{
		ft_printf("-----OBJS-----\n");
		scene.objs->hit(scene.objs->type);
		scene.objs = scene.objs->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	//t_mlx	data;

	if (check_args(argc, argv) == 1)
		return (1);
	scene = init_structs();
	if (check_map(argv[1], &scene) || scene.ambligth.init == false
		|| scene.camera.init == false)
	{
		print_shit(scene);
		ft_printf("Incorrect Map -- Concerning Situation");
		return (1);
	}
	print_shit(scene);
	//data.mlx = mlx_init();
	//data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "MINIRT");
	//mlx_hook(data.mlx_win, KEYDOWN, 0, key_down, (void *)&data);
	//mlx_loop(data.mlx);
	return (0);
}
