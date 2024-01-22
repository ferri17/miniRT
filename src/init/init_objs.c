/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/23 00:35:00 by fbosch           ###   ########.fr       */
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
	if (fill_sphere(sp->type.sp, split) || put_colors(&sp->materia.color,
			split[3]))
		return (1);
	if (ft_array_len(split) == 5)
	{
		if (ft_strcmp(split[4], "CHECKBOARD") == 0)
			sp->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		sp->materia.texture = DEFAULT;
	sp->get_color = get_color_sphere;
	sp->hit = hit_sphere;
	sp->get_position_pointer = get_position_sphere;
	sp->materia.specular = 1.0; //BORRAR
	sp->materia.metallic = 0.3; //BORRAR
	sp->materia.roughness = 256.0; //BORRAR
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
	if (fill_plane(pl->type.pl, split) || put_colors(&pl->materia.color,
			split[3]))
		return (1);
	if (check_dir(&pl->type.pl->normal))
		return (1);
	if (ft_array_len(split) == 5)
	{
		if (ft_strcmp(split[4], "CHECKBOARD") == 0)
			pl->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	pl->type.pl->normal = unit_vector(&pl->type.pl->normal);
	pl->get_color = get_color_plane;
	pl->hit = hit_plane;
	pl->get_position_pointer = get_position_plane;
	pl->materia.specular = 1.0; //BORRAR
	pl->materia.metallic = 0.5; //BORRAR
	pl->materia.roughness = 4.0; //BORRAR
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
	if (fill_cylinder(cy->type.cy, split) || put_colors(&cy->materia.color,
			split[5]))
		return (1);
	if (check_dir(&cy->type.cy->dir))
		return (1);
	if (ft_array_len(split) == 7)
	{
		if (ft_strcmp(split[6], "CHECKBOARD") == 0)
			cy->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		cy->materia.texture = DEFAULT;
	inti_func_cylinder(cy);
	cy->materia.specular = 1.0; //BORRAR
	cy->materia.metallic = 0.0; //BORRAR
	cy->materia.roughness = 4.0; //BORRAR
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
	if (fill_cone(cn->type.cn, split) || put_colors(&cn->materia.color,
			split[5]))
		return (1);
	if (check_dir(&cn->type.cn->dir))
		return (1);
	if (ft_array_len(split) == 7)
	{
		if (ft_strcmp(split[6], "CHECKBOARD") == 0)
			cn->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		cn->materia.texture = DEFAULT;
	inti_func_cone(cn);
	cn->materia.specular = 1.0; //BORRAR
	cn->materia.metallic = 0.0; //BORRAR
	cn->materia.roughness = 4.0; //BORRAR
	return (0);
}
