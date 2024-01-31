/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:00:58 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/29 13:04:29 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_texture_cone(t_scene *scene, t_world *cn, char **split)
{
	int	split_length;

	split_length = ft_array_len(split);
	if (split_length == 9)
		cn->materia.texture = DEFAULT;
	else if (split_length == 10)
	{
		if (ft_strcmp(split[9], "CHECKBOARD") == 0)
			cn->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else if (split_length == 11)
		return (bitmap_or_bumpmap_case(scene, cn, split, 9));
	else if (split_length == 12)
		return (bitmap_bumpmap_case(scene, cn, split, 9));
	return (0);
}

int	check_texture_cylinder(t_scene *scene, t_world *cy, char **split)
{
	int	split_length;

	split_length = ft_array_len(split);
	if (split_length == 9)
		cy->materia.texture = DEFAULT;
	else if (split_length == 10)
	{
		if (ft_strcmp(split[9], "CHECKBOARD") == 0)
			cy->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else if (split_length == 11)
		return (bitmap_or_bumpmap_case(scene, cy, split, 9));
	else if (split_length == 12)
		return (bitmap_bumpmap_case(scene, cy, split, 9));
	return (0);
}

int	check_texture_plane(t_scene *scene, t_world *pl, char **split)
{
	int	split_length;

	split_length = ft_array_len(split);
	if (split_length == 7)
		pl->materia.texture = DEFAULT;
	else if (split_length == 8)
	{
		if (ft_strcmp(split[7], "CHECKBOARD") == 0)
			pl->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else if (split_length == 9)
		return (bitmap_or_bumpmap_case(scene, pl, split, 7));
	else if (split_length == 10)
		return (bitmap_bumpmap_case(scene, pl, split, 7));
	return (0);
}

int	check_texture_sphere(t_scene *scene, t_world *sp, char **split)
{
	int	split_length;

	split_length = ft_array_len(split);
	if (split_length == 7)
		sp->materia.texture = DEFAULT;
	else if (split_length == 8)
	{
		if (ft_strcmp(split[7], "CHECKBOARD") == 0)
			sp->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else if (split_length == 9)
	{
		return (bitmap_or_bumpmap_case(scene, sp, split, 7));
	}
	else if (split_length == 10)
		return (bitmap_bumpmap_case(scene, sp, split, 7));
	return (0);
}
