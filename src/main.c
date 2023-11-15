/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/15 18:30:08 by apriego-         ###   ########.fr       */
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
	ft_printf("-----CAMERA-----\n");
	ft_printf("Coord: x:%d y:%d z:%d\n", scene.camera.coord.x, scene.camera.coord.y, scene.camera.coord.z);
	printf("Direct: x:%f y:%f z:%f\n", scene.camera.direct.x, scene.camera.direct.y, scene.camera.direct.z);
	ft_printf("FOV: %d\n", scene.camera.fov);
	ft_printf("-----AMBIENT-----\n");
	ft_printf("COLOR: R:%d G:%d B:%d\n", scene.ambligth.color.r, scene.ambligth.color.g, scene.ambligth.color.b);
	printf("RATIO: %f\n", scene.ambligth.ratio);
	ft_printf("-----LIGTH-----\n");
	ft_printf("Coord: x:%d y:%d z:%d\n", scene.ligth.coord.x, scene.ligth.coord.y, scene.ligth.coord.z);
	ft_printf("Direct: x:%d y:%d z:%d\n", scene.ligth.color.r, scene.ligth.color.g, scene.ligth.color.b);
	printf("BRIGT: %f\n", scene.ligth.brigt);	
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
