/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:39:19 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/14 15:52:19 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

static int	find_biggest(float n1, float n2)
{
	if (n1 < n2)
		return (1);
	return (-1);
}

static t_bresenh	init_bresenham_variables(t_line *line)
{
	t_bresenh	info;

	info.accept = 0;
	info.draw.start[X] = (int)round(line->start.axis[X]);
	info.draw.start[Y] = (int)round(line->start.axis[Y]);
	info.draw.end[X] = (int)round(line->end.axis[X]);
	info.draw.end[Y] = (int)round(line->end.axis[Y]);
	info.dx = abs(info.draw.end[X] - info.draw.start[X]);
	info.dy = abs(info.draw.end[Y] - info.draw.start[Y]);
	info.sx = find_biggest(info.draw.start[X], info.draw.end[X]);
	info.sy = find_biggest(info.draw.start[Y], info.draw.end[Y]);
	info.err = info.dx - info.dy;
	return (info);
}

static void	decide_error_bresenham(t_bresenh *info, int *i)
{
	info->err2 = 2 * info->err;
	if (info->err2 > -info->dy)
	{
		info->err -= info->dy;
		info->draw.start[X] += info->sx;
	}
	if (info->err2 < info->dx)
	{
		(*i)++;
		info->err += info->dx;
		info->draw.start[Y] += info->sy;
	}
}

void	my_mlx_pixel_put(t_mlx *img, int x, int y, int color)
{
	ft_memcpy(img->img.ptr + (y * img->img.pixel_bits + x * (img->img.line_bytes / 8)),
		&color, sizeof(int));
}

void	bresenham(t_mlx *data, t_line line)
{
	t_bresenh	info;
	int			col;
	int			i;

	i = 0;
	info = init_bresenham_variables(&line);
	if (!info.accept)
		return ;
	while (info.draw.start[X] != info.draw.end[X]
		|| info.draw.start[Y] != info.draw.end[Y])
	{
		col = 0;
		my_mlx_pixel_put(data, info.draw.start[X], info.draw.start[Y], col);
		decide_error_bresenham(&info, &i);
	}
	my_mlx_pixel_put(data, info.draw.end[X], info.draw.end[Y], col);
}
