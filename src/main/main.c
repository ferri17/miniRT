/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/29 14:28:31 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- MALLOCS NO PROTEGITS AL CREAR OBJECTES
	x CHECK OBJECTS CANT BE MOVED OVER LIMITS INT MAX
	- CONVERT ALL USER VECTORS TO UNIT VECTORS
	x AFEGIR LAMBERTIAN I ROUGHNESS ALS MATERIALS
	- ARREGLAR LLUMS CAMERA MOVEMENT (SEGFAULT NO LIGHTS)
	x FIX PLANE NORMALS
	x CAMERA NOMES POT APUNTAR A LA DIRECCIO Z
	x LIMITAR CANVAS SIZE
	- FIX BIAS FOR CON AUTOHIT
	- COMPROVAR OBJECTES DIR = 0,0,0
	- CANVIAR NOM CARPETA CHECKERBOARD
	- TEST COLORS LIKE 22.4,25,250 O 45,,,,,,,24,,,,,230
	- CHECK CAMERA UNIT VEC
*/
#include "MiniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (check_args(argc, argv) == 1)
		return (1);
	init_structs(&scene);
	init_mlx_windows(&scene.data, WIN_W, WIN_H);
	if (init_map(argv[1], &scene))
	{
		free_structs(scene);
		ft_printf_fd(STDERR_FILENO, ERR_INVALID_MAP);
		return (1);
	}
	render_image(&scene, IMG_W, IMG_H);
	mlx_hook(scene.data.mlx_win, KEYDOWN, 0, key_down, (void *)&scene);
	mlx_hook(scene.data.mlx_win, MOUSEMOVE, 0, mouse_move, (void *)&scene);
	mlx_hook(scene.data.mlx_win, MOUSEDOWN, 0, mouse_down, (void *)&scene);
	mlx_hook(scene.data.mlx_win, MOUSEUP, 0, mouse_up, (void *)&scene);
	mlx_hook(scene.data.mlx_win, DESTROY, 0, close_program, (void *)&scene);
	mlx_loop(scene.data.mlx);
	return (0);
}
