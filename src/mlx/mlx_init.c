/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:48:26 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/22 13:17:05 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	init_image(t_mlx *data)
{
	data->img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->img.buffer = mlx_get_data_addr(data->img.ptr,
			&data->img.pixel_bits, &data->img.line_bytes, &data->img.endian);
}
