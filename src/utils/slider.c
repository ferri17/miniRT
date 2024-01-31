/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:37:15 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/31 18:24:37 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_slider	init_slider(int min_value, int max_value, int *value, uint16_t len)
{
	t_slider	slider;

	slider.min_value = min_value;
	slider.max_value = max_value;
	slider.value = value;
	slider.length = len;
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
	else if (*(slider->value) < slider->min_value)
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

void	draw_slider(void *mlx_ptr, void *mlx_win, t_slider *slider)
{
	int	i;
	int	start;
	int	status_inc;

	slider->pos_x = (WIN_W / 2) - (slider->length * SLIDER_PX / 2);
	slider->pos_y = WIN_H - MD_PAD;
	start = slider->pos_x;
	status_inc = get_status_relative_increment(slider);
	if (status_inc >= 0)
	{
		i = 0;
		while (i < slider->length)
		{
			if (i < status_inc)
				mlx_string_put(mlx_ptr, mlx_win, start + (i * SLIDER_PX), WIN_H
					- MD_PAD, WHITE, "|");
			else
				mlx_string_put(mlx_ptr, mlx_win, start + (i * SLIDER_PX), WIN_H
					- MD_PAD, WHITE, "-");
			i++;
		}
	}
	else
		ft_printf("Slider error, invalid range\n");
}
