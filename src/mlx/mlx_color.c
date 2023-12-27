/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:08:36 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/26 20:54:49 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

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
