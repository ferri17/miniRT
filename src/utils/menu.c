/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 00:17:03 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/19 12:21:43 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	draw_selected_object(t_scene *scene)
{
	t_vec3	*center;
	char	value[100];

	center = scene->selected->get_position_pointer(&scene->selected->type);
	sprintf(value, "P(%.2f,%.2f,%.2f)", center->x, center->y, center->z);
	my_string_put(&scene->data, WIN_W - XL_PAD * 2, WIN_H - MD_PAD, value);
}

void	draw_menu(t_scene *scene)
{
	t_mlx	*data;
	char	fov[100];

	data = &scene->data;
	if (scene->selected)
		draw_selected_object(scene);
	if (scene->render_mode == EDIT_MODE)
		my_string_put(data, WIN_W - MD_PAD * 3, SM_PAD / 2, "[EDIT MODE]");
	else
		my_string_put(data, WIN_W - MD_PAD * 3, SM_PAD / 2, "[RENDER MODE]");
	draw_slider(data->mlx, data->mlx_win, &scene->slider, WIN_W / 2, WIN_H
		- MD_PAD);
	sprintf(fov, "Fov = %d", scene->camera.hfov);
	my_string_put(data, WIN_W / 2 - SM_PAD, WIN_H - SM_PAD * 3, fov);
}
