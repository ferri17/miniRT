/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/25 12:25:59 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	- MALLOCS NO PROTEGITS AL CREAR OBJECTES
	x CHECK OBJECTS CANT BE MOVED OVER LIMITS INT MAX
	- CONVERT ALL USER VECTORS TO UNIT VECTORS
	- AFEGIR LAMBERTIAN I ROUGHNESS ALS MATERIALS
	- ARREGLAR LLUMS CAMERA MOVEMENT (SEGFAULT NO LIGHTS)
	x FIX PLANE NORMALS
	x CAMERA NOMES POT APUNTAR A LA DIRECCIO Z
	x LIMITAR CANVAS SIZE
	- FIX BIAS FOR CON AUTOHIT
	- COMPROVAR OBJECTES DIR = 0,0,0
*/
#include "MiniRT.h"

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
	
	scene.objs->materia.img_tex.img_ptr = mlx_xpm_file_to_image(scene.data.mlx, "texture_src/earth.xpm", &scene.objs->materia.img_tex.w, &scene.objs->materia.img_tex.h);
	scene.objs->materia.img_tex.info = mlx_get_data_addr(scene.objs->materia.img_tex.img_ptr, &scene.objs->materia.img_tex.bpp, &scene.objs->materia.img_tex.sl, &scene.objs->materia.img_tex.endian);

	render_image(&scene, IMG_W, IMG_H);
	mlx_hook(scene.data.mlx_win, KEYDOWN, 0, key_down, (void *)&scene);
	mlx_hook(scene.data.mlx_win, MOUSEMOVE, 0, mouse_move, (void *)&scene);
	mlx_hook(scene.data.mlx_win, MOUSEDOWN, 0, mouse_down, (void *)&scene);
	mlx_hook(scene.data.mlx_win, MOUSEUP, 0, mouse_up, (void *)&scene);
	mlx_hook(scene.data.mlx_win, DESTROY, 0, close_program, (void *)&scene);
	mlx_loop(scene.data.mlx);
	return (0);
}
