/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:48:26 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/26 17:01:01 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	init_mlx_windows(t_mlx *data, int win_w, int win_h)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, win_w, win_h, "MINIRT");
}

void	init_mlx_image(t_mlx *data, int img_w, int img_h)
{
	data->img.ptr = mlx_new_image(data->mlx, img_w, img_h);
	data->img.buffer = mlx_get_data_addr(data->img.ptr,
			&data->img.pixel_bits, &data->img.line_bytes, &data->img.endian);
}
