/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:37:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/27 01:00:44 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_slider	init_slider(int min_value, int max_value, int *value, uint16_t length)
{
	t_slider	slider;

	slider.min_value = min_value;
	slider.max_value = max_value;
	slider.value = value;
	slider.length = length;
	slider.is_clicked = false;
	return (slider);
}

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

int	get_status_relative_increment(t_slider *slider)
{
	int		slider_range;
	float	ratio;

	slider_range = slider->max_value - slider->min_value;
	if (slider_range < 1)
		return (-1);
	ratio = (float)(slider_range) / (float)slider->length;
	return (*(slider->value) / ratio);
}

void	draw_slider(void *mlx_ptr, void *mlx_win, t_slider *slider, int x, int y)
{
	int	i;
	int	start;
	int	status_inc;

	slider->pos_x = x - (slider->length * SLIDER_PX / 2);
	slider->pos_y = y;
	start = slider->pos_x;
	status_inc = get_status_relative_increment(slider);
	if (status_inc >= 0)
	{
		i = 0;
		while (i < slider->length)
		{
			if (i < status_inc)
				mlx_string_put(mlx_ptr, mlx_win, start + (i * SLIDER_PX), y, WHITE, "|");
			else
				mlx_string_put(mlx_ptr, mlx_win, start + (i * SLIDER_PX), y, WHITE, "-");
			i++;
		}
	}
	else
		ft_printf("Slider error, invalid range\n");
}
