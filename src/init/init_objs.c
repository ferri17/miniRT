/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/26 16:28:53 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_world	*push_back(t_world *objs, t_scene *scene)
{
	if (objs)
	{
		while (objs->next)
			objs = objs->next;
		objs->next = malloc(sizeof(t_world));
		objs = objs->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		objs = scene->objs;
	}
	return (objs);
}

int	check_sphere(t_scene *scene, char **split)
{
	t_world	*sp;

	sp = push_back(scene->objs, scene);
	if (!sp)
		return (1);
	sp->next = NULL;
	sp->type.sp = malloc(sizeof(t_sphere));
	sp->free_type = free_sphere;
	if (fill_sphere(sp->type.sp, split) || check_materia(sp, split, 3)
		|| put_colors(&sp->materia.color, split[6]))
		return (1);
	if (check_texture_sphere(scene, sp, split))
		return (1);
	sp->get_color = get_color_sphere;
	sp->hit = hit_sphere;
	sp->get_position_pointer = get_position_sphere;
	sp->get_normal_map = get_normal_map_sphere;
	return (0);
}

int	check_plane(t_scene *scene, char **split)
{
	t_world	*pl;

	pl = push_back(scene->objs, scene);
	if (!pl)
		return (1);
	pl->next = NULL;
	pl->type.pl = malloc(sizeof(t_plane));
	pl->free_type = free_plane;
	if (fill_plane(pl->type.pl, split) || check_materia(pl, split, 3)
		|| put_colors(&pl->materia.color, split[6]))
		return (1);
	if (check_dir(&pl->type.pl->normal))
		return (1);
	if (check_texture_plane(scene, pl, split))
		return (1);
	pl->type.pl->normal = unit_vector(&pl->type.pl->normal);
	pl->get_color = get_color_plane;
	pl->hit = hit_plane;
	pl->get_position_pointer = get_position_plane;
	pl->get_normal_map = get_normal_map_plane;
	return (0);
}

int	check_cylinder(t_scene *scene, char **split)
{
	t_world	*cy;

	cy = push_back(scene->objs, scene);
	if (!cy)
		return (1);
	cy->next = NULL;
	cy->type.cy = malloc(sizeof(t_cylinder));
	cy->free_type = free_cylinder;
	if (fill_cylinder(cy->type.cy, split) || check_materia(cy, split, 5)
		|| put_colors(&cy->materia.color, split[8]))
		return (1);
	if (check_dir(&cy->type.cy->dir))
		return (1);
	if (check_texture_cylinder(scene, cy, split))
		return (1);
	inti_func_cylinder(cy);
	return (0);
}

int	check_cone(t_scene *scene, char **split)
{
	t_world	*cn;

	cn = push_back(scene->objs, scene);
	if (!cn)
		return (1);
	cn->next = NULL;
	cn->type.cn = malloc(sizeof(t_cone));
	cn->free_type = free_cone;
	if (fill_cone(cn->type.cn, split) || check_materia(cn, split, 5)
		|| put_colors(&cn->materia.color, split[8]))
		return (1);
	if (check_dir(&cn->type.cn->dir))
		return (1);
	if (check_texture_cone(scene, cn, split))
		return (1);
	inti_func_cone(cn);
	return (0);
}
