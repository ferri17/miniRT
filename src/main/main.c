/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2024/02/04 17:58:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		mlx_destroy_window(scene.data.mlx, scene.data.mlx_win);
		mlx_destroy(scene.data.mlx);
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
