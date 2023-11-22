/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:18:57 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/17 13:38:37 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_ligth(t_scene *scene, char **split)
{
	t_ligth	*lg;

	lg = scene->ligth;
	if (lg)
	{
		while (lg->next)
			lg = lg->next;
		lg->next = malloc(sizeof(t_ligth));
		lg = lg->next;
	}
	else
	{
		scene->ligth = malloc(sizeof(t_ligth));
		lg = scene->ligth;
	}
	if (!lg)
		return (1);
	lg->next = NULL;
	if (fill_light(lg, split))
		return (1);
	return (0);
}

t_scene	init_structs(void)
{
	t_scene	scene;

	scene.ambligth.init = false;
	scene.camera.init = false;
	scene.ligth = NULL;
	scene.objs = NULL;
	return (scene);
}
