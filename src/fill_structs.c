/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:24:41 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/13 19:41:27 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	put_colors(t_colors *colors, char **s_colors)
{
	int	gradient;

	gradient = ft_atod(s_colors[0]);
	if (ft_test_int(s_colors[0]) == 0 && gradient < 256 && gradient >= 0)
		colors->r = gradient;
	else
		return (1);
	gradient = ft_atoi(s_colors[1]);
	if (ft_test_int(s_colors[1]) == 0 && gradient < 256 && gradient >= 0)
		colors->g = gradient;
	else
		return (1);
	gradient = ft_atoi(s_colors[2]);
	if (ft_test_int(s_colors[2]) == 0 && gradient < 256 && gradient >= 0)
		colors->b = gradient;
	else
		return (1);
	return (0);
}

int	put_coord(t_coords *coord, char **coords)
{
	if (ft_test_double(coords[0], -1080, 1080) == 0)
		coord->x = ft_atod(coords[0]);
	else
		return (1);
	if (ft_test_double(coords[1], -1980, 1980) == 0)
		coord->y = ft_atod(coords[1]);
	else
		return (1);
	if (ft_test_double(coords[2], -1980, 1980) == 0)
		coord->z = ft_atod(coords[2]);
	else
		return (1);
	return (0);
}

int	put_direct(t_direction *direct, char **norm)
{
	if (ft_test_double(norm[0], -1.0, 1.0) == 0)
		direct->x = ft_atod(norm[0]);
	else
		return (1);
	if (ft_test_double(norm[1], -1.0, 1.0) == 0)
		direct->y = ft_atod(norm[1]);
	else
		return (1);
	if (ft_test_double(norm[2], -1.0, 1.0) == 0)
		direct->z = ft_atod(norm[2]);
	else
		return (1);
	return (0);
}

int	put_fov(int *fov, char *num)
{
	int	number;

	number = ft_atoi(num);
	if (ft_test_int(num) == 0 && number >= 0 && number <= 180)
		*fov = number;
	else
		return (1);
	return (0);
}

int	fill_ambient(t_scene *scene, char **split)
{
	double	ratio;
	char	**colors;

	if (ft_array_len(split) != 3)
		return (1);
	if (ft_test_double(split[1], 0.0, 1.0))
		return (1);
	ratio = ft_atod(split[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (1);
	scene->ambligth.ratio = ft_atod(split[1]);
	colors = ft_split(split[2], ',');
	if (!colors)
		return (1);
	if (ft_array_len(colors) != 3)
		return (ft_free_malloc_array(colors), 1);
	if (put_colors(&scene->ambligth.color, colors))
		return (ft_free_malloc_array(colors), 1);
	ft_free_malloc_array(colors);
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
	return (0);
}

int	fill_light(t_scene *scene, char **split)
{
	char	**coord;
	char	**color;

	if (ft_array_len(split) != 4)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3)
		return (ft_free_malloc_array(coord), 1);
	if (put_coord(&scene->ligth.coord, coord))
		return (1);
	ft_free_malloc_array(coord);
	if (ft_test_double(split[2], 0.0, 1.0))
		return (1);
	scene->ligth.brigt = ft_atod(split[2]);
	color = ft_split(split[3], ',');
	if (!color)
		return (1);
	if (ft_array_len(color) != 3)
		return (ft_free_malloc_array(color), 1);
	if (put_colors(&scene->ligth.color, color))
		return (ft_free_malloc_array(color), 1);
	return (0);
}

int	fill_sphere(t_sphere *sp, char **split)
{
	char	**coord;
	char	**color;

	if (ft_array_len(split) != 4)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3)
		return (ft_free_malloc_array(coord), 1);
	if (put_coord(&sp->coord, coord))
		return (1);
	ft_free_malloc_array(coord);
	if (ft_test_double(split[2], 0.0, 10000.0))
		return (1);
	sp->radius = ft_atod(split[2]);
	color = ft_split(split[3], ',');
	if (!color)
		return (1);
	if (ft_array_len(color) != 3)
		return (ft_free_malloc_array(color), 1);
	if (put_colors(&sp->colors, color))
		return (ft_free_malloc_array(color), 1);
	return (0);
}

// int	fill_plane(t_scene *scene, char **split)
// {

// }

// int	fill_cylinder(t_scene *scene, char **split)
// {

// }
