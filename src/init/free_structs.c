/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:13:21 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/12 13:12:26 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	free_light(t_ligth *ligth)
{
	t_ligth	*aux;

	aux = ligth;
	while (ligth)
	{
		ligth = ligth->next;
		free(aux);
		aux = ligth;
	}
}

void	free_obj(t_world *objs)
{
	t_world	*tmp;

	tmp = objs;
	while (objs)
	{
		objs = objs->next;
		tmp->free_type(tmp->type);
		free(tmp);
		tmp = objs;
	}
}

void	free_structs(t_scene scene)
{
	free_light(scene.ligth);
	free_obj(scene.objs);
}
