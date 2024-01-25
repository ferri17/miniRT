/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:51:31 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/25 15:57:15 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	fill_sphere(t_sphere *sp, char **split)
{
	char	**coord;

	if (ft_array_len(split) < 7 || ft_array_len(split) > 10)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3)
		return (ft_free_malloc_array(coord), 1);
	if (put_coord(&sp->center, coord))
		return (1);
	ft_free_malloc_array(coord);
	if (ft_test_double(split[2], MIN_SIZE, MAX_SIZE))
		return (1);
	sp->radius = ft_atod(split[2]) / 2;
	return (0);
}

int	fill_plane(t_plane *pl, char **split)
{
	char	**coord;
	char	**norm;

	if (ft_array_len(split) < 7 || ft_array_len(split) > 8)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3 || put_coord(&pl->center, coord))
		return (ft_free_malloc_array(coord), 1);
	ft_free_malloc_array(coord);
	norm = ft_split(split[2], ',');
	if (!norm)
		return (1);
	if (ft_array_len(norm) != 3 || put_dir(&pl->normal, norm))
		return (ft_free_malloc_array(norm), 1);
	ft_free_malloc_array(norm);
	return (0);
}

int	fill_cylinder(t_cylinder *cy, char **split)
{
	char	**coord;
	char	**norm;

	if (ft_array_len(split) < 9 || ft_array_len(split) > 10)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3 || put_coord(&cy->center, coord))
		return (ft_free_malloc_array(coord), 1);
	ft_free_malloc_array(coord);
	norm = ft_split(split[2], ',');
	if (!norm)
		return (1);
	if (ft_array_len(norm) != 3 || put_dir(&cy->dir, norm))
		return (ft_free_malloc_array(norm), 1);
	ft_free_malloc_array(norm);
	if (ft_test_double(split[3], MIN_SIZE, MAX_SIZE)
		|| ft_test_double(split[4], MIN_SIZE, MAX_SIZE))
		return (1);
	cy->radius = ft_atod(split[3]) / 2;
	cy->height = ft_atod(split[4]);
	return (0);
}

int	fill_cone(t_cone *cn, char **split)
{
	char	**coord;
	char	**norm;

	if (ft_array_len(split) < 9 || ft_array_len(split) > 10)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3 || put_coord(&cn->center, coord))
		return (ft_free_malloc_array(coord), 1);
	ft_free_malloc_array(coord);
	norm = ft_split(split[2], ',');
	if (!norm)
		return (1);
	if (ft_array_len(norm) != 3 || put_dir(&cn->dir, norm))
		return (ft_free_malloc_array(norm), 1);
	ft_free_malloc_array(norm);
	if (ft_test_double(split[3], MIN_SIZE, MAX_SIZE)
		|| ft_test_double(split[4], 1, 178))
		return (1);
	cn->height = ft_atod(split[3]);
	cn->angle = ft_atod(split[4]);
	return (0);
}
