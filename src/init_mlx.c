/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:08:36 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/16 12:34:53 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

// int	close_program(t_mlx *data, int exit_code)
// {
// 	mlx_destroy_window(data->mlx, data->mlx_win);
// 	mlx_destroy(data->mlx);
// 	exit(exit_code);
// }

// int	key_down(int key, void *param)
// {
// 	t_mlx	*data;

// 	data = (t_mlx *)param;
// 	if (key == ESC_KEY)
// 		close_program(data, EXIT_SUCCESS);
// 	return (0);
// }

// t_mlx	init_mlx(void)
// {
// 	t_mlx	data;

// 	data.mlx = mlx_init();
// 	data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "MINIRT");
// 	mlx_hook(data.mlx_win, KEYDOWN, 0, key_down, (void *)&data);
// 	return (data);
// }

/*
	- Scene needs to have a camera and ambient light
	- Many empty lines segfault
*/