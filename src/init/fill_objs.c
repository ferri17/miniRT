/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:51:31 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/28 14:07:09 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	fill_sphere(t_sphere *sp, char **split)
{
	int		split_length;
	char	**coord;

	split_length = ft_array_len(split);
	if (split_length < 7 || split_length > 10)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3)
		return (ft_free_malloc_array(coord), 1);
	if (put_coord(&sp->center, coord))
		return (ft_free_malloc_array(coord), 1);
	ft_free_malloc_array(coord);
	if (ft_test_double(split[2], MIN_SIZE, MAX_SIZE))
		return (1);
	sp->radius = ft_atod(split[2]) / 2.0;
	return (0);
}

int	fill_plane(t_plane *pl, char **split)
{
	int		split_length;
	char	**coord;
	char	**norm;

	split_length = ft_array_len(split);
	if (split_length < 7 || split_length > 10)
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
	int		split_length;
	char	**coord;
	char	**norm;

	split_length = ft_array_len(split);
	if (split_length < 9 || split_length > 12)
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
	cy->radius = ft_atod(split[3]) / 2.0;
	cy->height = ft_atod(split[4]);
	return (0);
}

int	fill_cone(t_cone *cn, char **split)
{
	int		split_length;
	char	**coord;
	char	**norm;

	split_length = ft_array_len(split);
	if (split_length < 9 || split_length > 12)
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
