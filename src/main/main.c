/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/14 15:45:32 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- MALLOCS NO PROTEGITS AL CREAR OBJECTES
	- CHECK OBJECTS CANT BE MOVED OVER LIMITS INT MAX
	- CONVERT ALL USER VECTORS TO UNIT VECTORS
	- AFEGIR LAMBERTIAN I ROUGHNESS ALS MATERIALS
*/
#include "MiniRT.h"

void print_shit(t_scene scene)
{
	printf("-----CAMERA-----\n");
	printf("Coord: x:%f y:%f z:%f\n", scene.camera.center.x, scene.camera.center.y, scene.camera.center.z);
	printf("Direct: x:%f y:%f z:%f\n", scene.camera.dir.x, scene.camera.dir.y, scene.camera.dir.z);
	printf("FOV: %d\n", scene.camera.hfov);
	printf("-----AMBIENT-----\n");
	printf("COLOR: R:%f G:%f B:%f\n", scene.amblight.color.x, scene.amblight.color.y, scene.amblight.color.z);
	printf("RATIO: %f\n", scene.amblight.ratio);
	printf("-----LIGTH-----\n");
	//printf("BRIGT: %f\n", scene.ligth.brigt);
	while (scene.objs)
	{
		ft_printf("-----OBJS-----\n");
		ft_printf("%d\n", scene.objs->materia.texture);
		//scene.objs->hit(scene.objs->type);
		scene.objs = scene.objs->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (check_args(argc, argv) == 1)
		return (1);
	init_structs(&scene);
	if (init_map(argv[1], &scene))
	{
		free_structs(scene);
		ft_printf_fd(STDERR_FILENO, ERR_INVALID_MAP);
		return (1);
	}
	init_mlx_windows(&scene.data, WIN_W, WIN_H);
	render_image(&scene, IMG_W, IMG_H);
	mlx_hook(scene.data.mlx_win, KEYDOWN, 0, key_down, (void *)&scene);
	mlx_hook(scene.data.mlx_win, MOUSEUP, 0, mouse_up, (void *)&scene);
	mlx_hook(scene.data.mlx_win, DESTROY, 0, close_program, (void *)&scene);
	mlx_loop(scene.data.mlx);
	return (0);
}
