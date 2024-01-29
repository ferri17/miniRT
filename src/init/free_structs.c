/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:13:21 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/29 14:22:53 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	free_light(t_light *light)
{
	t_light	*aux;

	aux = light;
	while (light)
	{
		light = light->next;
		free(aux);
		aux = light;
	}
}

void	free_obj(t_scene sc, t_world *objs)
{
	t_world	*tmp;

	tmp = objs;
	while (objs)
	{
		objs = objs->next;
		tmp->free_type(tmp->type);
		if (tmp->materia.bit.img_ptr)
			mlx_destroy_image(sc.data.mlx, tmp->materia.bit.img_ptr);
		if (tmp->materia.bump.img_ptr)
			mlx_destroy_image(sc.data.mlx, tmp->materia.bump.img_ptr);
		free(tmp);
		tmp = objs;
	}
}

void	free_structs(t_scene scene)
{
	free_light(scene.light);
	free_obj(scene, scene.objs);
}
