/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:46:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/03 20:43:06 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	close_program(t_scene *scene, int exit_code)
{
	mlx_destroy_image(scene->data.mlx, scene->data.img.ptr);
	mlx_destroy_window(scene->data.mlx, scene->data.mlx_win);
	mlx_destroy(scene->data.mlx);
	exit(exit_code);
}

void	move_camera(t_scene *scene, int key)
{
	const double	move = 0.2;

	if (key == A_KEY)
	{
		scene->light->center.x -= move;
		//scene->light->dir.x -= move;
	}
	else if (key == D_KEY)
	{
		scene->light->center.x += move;
		//scene->light->dir.x += move;
	}
	if (key == W_KEY)
	{
		scene->light->center.y += move;
		//scene->light->dir.y += move;

	}
	else if (key == S_KEY)
	{
		scene->light->center.y -= move;
		//scene->light->dir.y -= move;
	}
	if (key == ONE_KEY)
	{
		scene->light->center.z += move;
		//scene->light->dir.z += move;
	}
	else if (key == TWO_KEY)
	{
		scene->light->center.z -= move;
		//scene->camera.dir.z -= move;
	}
	render_image(scene, IMG_W, IMG_H);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_scene	*scene;
	t_world	*tmp;

	scene = (t_scene *)param;
	if (button == LEFT_CLICK)
	{
		tmp = select_object(scene, x, y);
		if (tmp)
		{
			scene->selected = tmp;
			ft_printf("Hit object\n");
		}
	}
	return (0);
}

int	key_down(int key, void *param)
{
	t_scene	*scene;
	scene = (t_scene *)param;
	if (key == ESC_KEY)
		close_program(scene, EXIT_SUCCESS);
	else if (key == A_KEY || key == D_KEY || key == W_KEY || key == S_KEY
			|| key == ONE_KEY || key == TWO_KEY)
		move_camera(scene, key);
	return (0);
}
