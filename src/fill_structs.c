/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:24:41 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/17 13:26:36 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	fill_ambient(t_scene *scene, char **split)
{
	double	ratio;

	if (ft_array_len(split) != 3)
		return (1);
	if (ft_test_double(split[1], 0.0, 1.0))
		return (1);
	ratio = ft_atod(split[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (1);
	scene->ambligth.ratio = ft_atod(split[1]);
	if (put_colors(&scene->ambligth.color, split[2]))
		return (1);
	scene->ambligth.init = true;
	return (0);
}

int	fill_camera(t_scene *scene, char **split)
{
	char	**view;
	char	**norm;

	if (ft_array_len(split) != 4)
		return (1);
	view = ft_split(split[1], ',');
	if (!view)
		return (1);
	if (ft_array_len(view) != 3)
		return (ft_free_malloc_array(view), 1);
	if (put_coord(&scene->camera.coord, view))
		return (ft_free_malloc_array(view), 1);
	ft_free_malloc_array(view);
	norm = ft_split(split[2], ',');
	if (!norm)
		return (1);
	if (ft_array_len(norm) != 3)
		return (ft_free_malloc_array(norm), 1);
	if (put_direct(&scene->camera.direct, norm))
		return (ft_free_malloc_array(norm), 1);
	ft_free_malloc_array(norm);
	if (put_fov(&scene->camera.fov, split[3]))
		return (1);
	scene->camera.init = true;
	return (0);
}

int	fill_light(t_ligth *ligth, char **split)
{
	char	**coord;

	if (ft_array_len(split) != 4)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3)
		return (ft_free_malloc_array(coord), 1);
	if (put_coord(&ligth->coord, coord))
		return (1);
	ft_free_malloc_array(coord);
	if (ft_test_double(split[2], 0.0, 1.0))
		return (1);
	ligth->	brigt = ft_atod(split[2]);
	if (put_colors(&ligth->color, split[3]))
		return (1);
	return (0);
}
