/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:42:33 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/14 15:53:27 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

static void	init_cube(t_point *cube)
{
	cube[0].axis[X] = -30;
	cube[0].axis[Y] = -30;
	cube[0].axis[Z] = 30;
	cube[1].axis[X] = 30;
	cube[1].axis[Y] = -30;
	cube[1].axis[Z] = 30;
	cube[2].axis[X] = 30;
	cube[2].axis[Y] = 30;
	cube[2].axis[Z] = 30;
	cube[3].axis[X] = -30;
	cube[3].axis[Y] = 30;
	cube[3].axis[Z] = 30;
	cube[4].axis[X] = -30;
	cube[4].axis[Y] = -30;
	cube[4].axis[Z] = -30;
	cube[5].axis[X] = 30;
	cube[5].axis[Y] = -30;
	cube[5].axis[Z] = -30;
	cube[6].axis[X] = 30;
	cube[6].axis[Y] = 30;
	cube[6].axis[Z] = -30;
	cube[7].axis[X] = -30;
	cube[7].axis[Y] = 30;
	cube[7].axis[Z] = -30;
}

static void	draw_axis(t_mlx *data, t_point *cube)
{
	t_line	line;

	line.start = cube[0];
	line.end = cube[4];
	line.start.color = data->map.col_axis[Z];
	line.end.color = data->map.col_axis[Z];
	bresenham(data, line);
	line.start = cube[4];
	line.end = cube[5];
	line.start.color = data->map.col_axis[X];
	line.end.color = data->map.col_axis[X];
	bresenham(data, line);
	line.start = cube[4];
	line.end = cube[7];
	line.start.color = data->map.col_axis[Y];
	line.end.color = data->map.col_axis[Y];
	bresenham(data, line);
}

static void	draw_edge_cube(t_mlx *data, t_point *cube, int i)
{
	t_line	line;

	if (i == 0 || i == 2 || i == 4 || i == 6)
	{
		line.start = cube[i];
		line.end = cube[i + 1];
		bresenham(data, line);
		if (i == 0 || i == 4)
		{
			line.start = cube[i];
			line.end = cube[i + 3];
		}
		else
		{
			line.start = cube[i];
			line.end = cube[i - 1];
		}
		bresenham(data, line);
	}
	if (i == 0 || i == 1 || i == 2 || i == 3)
	{
		line.start = cube[i];
		line.end = cube[i + 4];
		bresenham(data, line);
	}
}

void	draw_extras(t_mlx *data)
{
	t_point	cube[CUBE_VERTEX];
	int		i;

	init_cube(cube);
	i = 0;
	while (i < CUBE_VERTEX)
	{
		draw_edge_cube(data, cube, i);
		i++;
	}
	draw_axis(data, cube);
}