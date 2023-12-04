/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/04 18:49:55 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_sphere(t_scene *scene, char **split)
{
	t_world	*sp;

	sp = scene->objs;
	if (sp)
	{
		while (sp->next)
			sp = sp->next;
		sp->next = malloc(sizeof(t_world));
		sp = sp->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		sp = scene->objs;
	}
	if (!sp)
		return (1);
	sp->next = NULL;
	sp->type.sp = malloc(sizeof(t_sphere)); //PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	if (fill_sphere(sp->type.sp, split) || put_colors(&sp->color, split[3]))
		return (1);
	sp->hit = hit_sphere;
	sp->move = move_sphere;
	return (0);
}

int	check_plane(t_scene *scene, char **split)
{
	t_world	*pl;

	pl = scene->objs;
	if (pl)
	{
		while (pl->next)
			pl = pl->next;
		pl->next = malloc(sizeof(t_world));
		pl = pl->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		pl = scene->objs;
	}
	if (!pl)
		return (1);
	pl->next = NULL;
	pl->type.pl = malloc (sizeof(t_plane)); //PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	if (fill_plane(pl->type.pl, split) || put_colors(&pl->color, split[3]))
		return (1);
	pl->hit = hit_plane;
	pl->move = move_plane;
	return (0);
}

int	check_cylinder(t_scene *scene, char **split)
{
	t_world	*cy;

	cy = scene->objs;
	if (cy)
	{
		while (cy->next)
			cy = cy->next;
		cy->next = malloc(sizeof(t_world));
		cy = cy->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		cy = scene->objs;
	}
	if (!cy)
		return (1);
	cy->next = NULL;
	cy->type.cy = malloc(sizeof(t_cylinder)); //PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	if (fill_cylinder(cy->type.cy, split) || put_colors(&cy->color, split[5]))
		return (1);
	cy->hit = hit_cylinder;
	cy->move = move_cylinder;
	return (0);
}
