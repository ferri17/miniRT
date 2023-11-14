/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/14 12:40:14 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_sphere(t_scene *scene, char **split)
{
	t_sphere	*sp;

	sp = scene->objs.sp;
	if (sp)
	{
		while (sp->next)
			sp = sp->next;
		sp->next = malloc(sizeof(t_sphere));
		sp = sp->next;
	}
	else
	{
		scene->objs.sp = malloc(sizeof(t_sphere));
		sp = scene->objs.sp;
	}
	if (!sp)
		return (1);
	sp->next = NULL;
	if (fill_sphere(sp, split))
		return (1);
	return (0);
}

int	check_plane(t_scene *scene, char **split)
{
	t_plane	*pl;

	pl = scene->objs.pl;
	if (pl)
	{
		while (pl->next)
			pl = pl->next;
		pl->next = malloc(sizeof(t_plane));
		pl = pl->next;
	}
	else
	{
		scene->objs.pl = malloc(sizeof(t_plane));
		pl = scene->objs.pl;
	}
	if (!pl)
		return (1);
	pl->next = NULL;
	if (fill_plane(pl, split))
		return (1);
	return (0);
}

int	check_cylinder(t_scene *scene, char **split)
{
	t_cylinder	*cy;

	cy = scene->objs.cy;
	if (cy)
	{
		while (cy->next)
			cy = cy->next;
		cy->next = malloc(sizeof(t_cylinder));
		cy = cy->next;
	}
	else
	{
		scene->objs.cy = malloc(sizeof(t_cylinder));
		cy = scene->objs.cy;
	}
	if (!cy)
		return (1);
	cy->next = NULL;
	if (fill_cylinder(cy, split))
		return (1);
	return (0);
}
