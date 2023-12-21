/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 02:36:21 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/21 19:37:34 by fbosch           ###   ########.fr       */
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

void	drag_object(t_scene *scene, int x, int y)
{
	static int	last_x = 0;
	static int	last_y = 0;
	static bool	first_click = true;
	t_vec3	*vector;
	t_vec3	move;

	//ft_printf("a\n");
	if (scene->selected == NULL)
		return ;
	vector = scene->selected->get_position_pointer(&scene->selected->type);
	if (first_click)
	{
		first_click = false;
		last_x = x;
		last_y = y;
	}
	move = (t_vec3){(double)(x - last_x) / 1000.0, -(double)(y - last_y) / 1000.0, 0};
	*vector = add_vec3(vector, &move);
	last_x = x;
	last_y = y;
}
