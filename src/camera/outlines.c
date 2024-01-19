/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outlines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:54:06 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/19 12:27:53 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

bool	neighbour_diff(int pixel, int next, int edge, int *mask)
{
	int	pxl_nb;

	pxl_nb = IMG_H * IMG_W;
	if (edge < 0 || next % IMG_W != edge)
		return (is_within(next, 0, pxl_nb) && mask[pixel] != mask[next]);
	return (false);
}

void	outline_neighbour_pixels(int *img, int *mask, int i)
{
	if (neighbour_diff(i, i - IMG_W, -1, mask))
		img[i - IMG_W] = BLUE;
	else if (neighbour_diff(i, i - IMG_W + 1, 0, mask))
		img[i - IMG_W + 1] = BLUE;
	else if (neighbour_diff(i, i + 1, 0, mask))
		img[i + 1] = BLUE;
	else if (neighbour_diff(i, i + IMG_W + 1, 0, mask))
		img[i + IMG_W + 1] = BLUE;
	else if (neighbour_diff(i, i + IMG_W, -1, mask))
		img[i + IMG_W] = BLUE;
	else if (neighbour_diff(i, i + IMG_W - 1, IMG_W - 1, mask))
		img[i + IMG_W - 1] = BLUE;
	else if (neighbour_diff(i, i - 1, IMG_W - 1, mask))
		img[i - 1] = BLUE;
	else if (neighbour_diff(i, i - IMG_W - 1, IMG_W - 1, mask))
		img[i - IMG_W - 1] = BLUE;
}

void	draw_outlines(t_scene *scene)
{
	t_mlx	*data;
	int		*img;
	int		i;
	int		pxl_nb;

	pxl_nb = IMG_H * IMG_W;
	data = &scene->data;
	img = (int *)data->img.buffer;
	if (scene->selected)
	{
		i = 0;
		while (i < pxl_nb)
		{
			if (scene->select_mask[i] == WHITE)
				outline_neighbour_pixels(img, scene->select_mask, i);
			i++;
		}
	}
	free (scene->select_mask);
	scene->select_mask = NULL;
}
