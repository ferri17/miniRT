/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:46:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/11 23:05:02 by fbosch           ###   ########.fr       */
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
	t_vec3	*vector;

	if (scene->selected == NULL)
		return ;
	vector = scene->selected->get_position_pointer(&scene->selected->type);
	if (key == A_KEY)
		vector->x += -MOVE;
	else if (key == D_KEY)
		vector->x += +MOVE;
	else if (key == W_KEY)
		vector->y += +MOVE;
	else if (key == S_KEY)
		vector->y += -MOVE;
	else if (key == ONE_KEY)
		vector->z += +MOVE;
	else if (key == TWO_KEY)
		vector->z += -MOVE;
	render_image(scene, IMG_W, IMG_H);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (button == LEFT_CLICK)
	{
		scene->selected = select_object(scene, x, y);
		render_image(scene, IMG_W, IMG_H);
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
	else if (key == J_KEY)
	{
		scene->light->center.x -= MOVE;
		render_image(scene, IMG_W, IMG_H);
	}
	else if (key == K_KEY)
	{
		scene->light->center.y -= MOVE;
		render_image(scene, IMG_W, IMG_H);
	}
	else if (key == L_KEY)
	{
		scene->light->center.x += MOVE;
		render_image(scene, IMG_W, IMG_H);
	}
	else if (key == I_KEY)
	{
		scene->light->center.y += MOVE;
		render_image(scene, IMG_W, IMG_H);
	}
	return (0);
}
