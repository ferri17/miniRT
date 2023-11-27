/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/27 16:30:46 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- MALLOCS NO PROTEGITS AL CREAR OBJECTES
*/
#include "MiniRT.h"

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
		//scene.objs->hit(scene.objs->type);
		scene.objs = scene.objs->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (check_args(argc, argv) == 1)
		return (1);
	scene = init_structs();
	if (init_map(argv[1], &scene))
	{
		print_shit(scene);
		ft_printf_fd(STDERR_FILENO, ERR_INVALID_MAP);
		return (1);
	}
	init_mlx_windows(&scene.data, WIN_W, WIN_H);
	render_image(&scene, IMG_W, IMG_H);
	mlx_hook(scene.data.mlx_win, KEYDOWN, 0, key_down, (void *)&scene);
	mlx_hook(scene.data.mlx_win, DESTROY, 0, close_program, (void *)&scene);
	mlx_loop(scene.data.mlx);
	//print_shit(scene);
	//data.mlx = mlx_init();
	//data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "MINIRT");
	//mlx_hook(data.mlx_win, KEYDOWN, 0, key_down, (void *)&data);
	//mlx_loop(data.mlx);
	return (0);
}
