/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:08:36 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/20 01:10:19 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	init_image(t_mlx *data)
{
	data->img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->img.buffer = mlx_get_data_addr(data->img.ptr,
			&data->img.pixel_bits, &data->img.line_bytes, &data->img.endian);
}

int	my_put_pixel(t_mlx *data, int x, int y, int color)
{
	int	pixel;

	if (data->img.pixel_bits != 32)
		color = mlx_get_color_value(data->mlx, color);
	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return (1);
	pixel = (data->img.line_bytes * y) + (x * data->img.pixel_bits / 8);
	set_color(&data->img, pixel, color);
	return (0);
}

void	set_color(t_image *img, int pixel, int color)
{
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = color >> 24;
		img->buffer[pixel + 1] = color >> 16 & 0xFF;
		img->buffer[pixel + 2] = color >> 8 & 0xFF;
		img->buffer[pixel + 3] = color & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->buffer[pixel + 0] = color & 0xFF;
		img->buffer[pixel + 1] = color >> 8 & 0xFF;
		img->buffer[pixel + 2] = color >> 16 & 0xFF;
		img->buffer[pixel + 3] = color >> 24;
	}
}

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