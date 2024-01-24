/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:18:57 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/22 00:54:33 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_light(t_scene *scene, char **split)
{
	t_light	*lg;

	lg = scene->light;
	if (lg)
	{
		while (lg->next)
			lg = lg->next;
		lg->next = malloc(sizeof(t_light));
		lg = lg->next;
	}
	else
	{
		scene->light = malloc(sizeof(t_light));
		lg = scene->light;
	}
	if (!lg)
		return (1);
	lg->next = NULL;
	if (fill_light(lg, split))
		return (1);
	return (0);
}

void	init_structs(t_scene *scene)
{
	scene->amblight.init = false;
	scene->camera.init = false;
	scene->objs = NULL;
	scene->data.img.ptr = NULL;
	scene->light = NULL;
	scene->render_mode = RAYTRACE_MODE;
	scene->selected = NULL;
	scene->bg_color = (t_color){0, 0, 0};
	scene->slider = init_slider(1, 179, &scene->camera.hfov, 50);
	scene->select_mask = NULL;
}
