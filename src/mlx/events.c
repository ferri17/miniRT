/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 02:36:21 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/19 02:41:10 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	update_slider(t_slider *slider, int x)
{
	float	ratio;

	ratio = (float)(x - slider->pos_x) / (float)(slider->length * SLIDER_PX);
	*(slider->value) = (slider->max_value - slider->min_value) * ratio;
	if (*(slider->value) > slider->max_value)
		*(slider->value) = slider->max_value;
	else if(*(slider->value) < slider->min_value)
		*(slider->value) = slider->min_value;
}

int	close_program(t_scene *scene, int exit_code)
{
	free_structs(*scene);
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
}
