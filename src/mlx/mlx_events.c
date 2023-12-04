/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:46:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/04 19:48:29 by fbosch           ###   ########.fr       */
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

void	move_object(t_scene *scene, int key)
{
	t_vec3	move;

	move = (t_vec3){0.0, 0.0, 0.0};
	if (key == A_KEY)
		move.x = -MOVE;
	else if (key == D_KEY)
		move.x = +MOVE;
	else if (key == W_KEY)
		move.y = +MOVE;
	else if (key == S_KEY)
		move.y = -MOVE;
	else if (key == ONE_KEY)
		move.z = +MOVE;
	else if (key == TWO_KEY)
		move.z = -MOVE;
	scene->selected->move(&scene->selected->type, &move);
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
			scene->selected = tmp;
	}
	return (0);
}

void	change_render_mode(t_scene *scene)
{
	scene->render_mode = (scene->render_mode + 1) % 2; 
	render_image(scene, IMG_W, IMG_H);
}


int	key_down(int key, void *param)
{
	t_scene	*scene;
	scene = (t_scene *)param;
	if (key == ESC_KEY)
		close_program(scene, EXIT_SUCCESS);
	else if (key == A_KEY || key == D_KEY || key == W_KEY || key == S_KEY
			|| key == ONE_KEY || key == TWO_KEY)
		move_object(scene, key);
	else if (key == M_KEY)
		change_render_mode(scene);
	return (0);
}
