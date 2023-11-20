/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:24:41 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/20 01:06:57 by fbosch           ###   ########.fr       */
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
	char	**center;
	char	**orientation;

	if (ft_array_len(split) != 4)
		return (1);
	center = ft_split(split[1], ',');
	if (!center)
		return (1);
	if (ft_array_len(center) != 3)
		return (ft_free_malloc_array(center), 1);
	if (put_coord(&scene->camera.center, center))
		return (ft_free_malloc_array(center), 1);
	ft_free_malloc_array(center);
	orientation = ft_split(split[2], ',');
	if (!orientation)
		return (1);
	if (ft_array_len(orientation) != 3)
		return (ft_free_malloc_array(orientation), 1);
	if (put_dir(&scene->camera.dir, orientation))
		return (ft_free_malloc_array(orientation), 1);
	ft_free_malloc_array(orientation);
	if (put_fov(&scene->camera.hfov, split[3]))
		return (1);
	scene->camera.init = true;
	return (0);
}

int	fill_light(t_scene *scene, char **split)
{
	char	**coord;

	if (ft_array_len(split) != 4)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3)
		return (ft_free_malloc_array(coord), 1);
	if (put_coord(&scene->ligth.center, coord))
		return (1);
	ft_free_malloc_array(coord);
	if (ft_test_double(split[2], 0.0, 1.0))
		return (1);
	scene->ligth.brigt = ft_atod(split[2]);
	if (put_colors(&scene->ligth.color, split[3]))
		return (1);
	return (0);
}
