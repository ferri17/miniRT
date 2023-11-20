/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/20 00:19:13 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"
#include <stdio.h>

void	hit_sphere(t_objects obj)
{
	t_sphere	*sp;

	sp = obj.sp;
	printf("Sphere: Color: r: %f g: %f b: %f\n", sp->color.e[R], sp->color.e[G], sp->color.e[B]);
}

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
	sp->type.sp = malloc(sizeof(t_sphere));
	if (fill_sphere(sp->type.sp, split))
		return (1);
	sp->hit = hit_sphere;
	return (0);
}

void	hit_plane(t_objects obj)
{
	t_plane	*pl;

	pl = obj.pl;
	printf("Plane: Color: r: %f g: %f b: %f\n", pl->color.e[R], pl->color.e[G], pl->color.e[B]);
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
	pl->type.pl = malloc (sizeof(t_plane));
	if (fill_plane(pl->type.pl, split))
		return (1);
	pl->hit = hit_plane;
	return (0);
}

void	hit_cylinder(t_objects obj)
{
	t_cylinder	*cy;

	cy = obj.cy;
	printf("Cylinder: Color: r: %f g: %f b: %f\n", cy->color.e[R], cy->color.e[G], cy->color.e[B]);
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
	cy->type.cy = malloc(sizeof(t_cylinder));
	if (fill_cylinder(cy->type.cy, split))
		return (1);
	cy->hit = hit_cylinder;
	return (0);
}
