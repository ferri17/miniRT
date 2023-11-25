/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:48:26 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/25 11:46:31 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	init_mlx_windows(t_mlx *data, int win_width, int win_height)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, win_width, win_height, "MINIRT");
}

void	init_mlx_image(t_mlx *data, int img_width, int img_height)
{
	data->img.ptr = mlx_new_image(data->mlx, img_width, img_height);
	data->img.buffer = mlx_get_data_addr(data->img.ptr,
			&data->img.pixel_bits, &data->img.line_bytes, &data->img.endian);
}
