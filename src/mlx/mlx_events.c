/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:46:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/27 12:41:44 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	close_program(t_scene *scene, int exit_code)
{
	mlx_destroy_window(scene->data.mlx, scene->data.mlx_win);
	mlx_destroy(scene->data.mlx);
	exit(exit_code);
}

void	move_camera(t_scene *scene, double x, double z)
{
	scene->camera.center.e[X] += x;
	scene->camera.center.e[Z] += z;
	render_image(scene, IMG_W, IMG_H);
}

int	key_down(int key, void *param)
{
	t_scene	*scene;
	scene = (t_scene *)param;
	if (key == ESC_KEY)
		close_program(scene, EXIT_SUCCESS);
	else if (key == A_KEY)
		move_camera(scene, -0.2, 0);
	else if (key == D_KEY)
		move_camera(scene, 0.2, 0);
	else if (key == W_KEY)
		move_camera(scene, 0, 0.2);
	else if (key == S_KEY)
		move_camera(scene, 0, -0.2);
	return (0);
}
