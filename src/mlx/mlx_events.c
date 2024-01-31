/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:46:29 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/31 17:31:18 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	mouse_move(int x, int y, void *param)
{
	t_scene		*scene;
	t_slider	*slider;

	(void)y;
	scene = (t_scene *)param;
	slider = &scene->slider;
	if (slider->is_clicked)
	{
		update_slider(slider, x);
		render_image(scene, IMG_W, IMG_H);
	}
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_scene		*scene;
	t_slider	*slider;

	scene = (t_scene *)param;
	slider = &scene->slider;
	if (button == LEFT_CLICK)
	{
		if (x >= slider->pos_x && x <= (slider->pos_x + slider->length
				* SLIDER_PX) && y >= slider->pos_y && y <= slider->pos_y
			+ SLIDER_HEIGHT)
		{
			slider->is_clicked = true;
		}
	}
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_scene		*scene;
	t_slider	*slider;

	scene = (t_scene *)param;
	slider = &scene->slider;
	if (button == LEFT_CLICK)
	{
		if (slider->is_clicked == true)
		{
			slider->is_clicked = false;
			update_slider(slider, x);
		}
		else
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
		scene->render_mode = (scene->render_mode + 1) % 2;
	render_image(scene, IMG_W, IMG_H);
	return (0);
}
