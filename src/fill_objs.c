/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:51:31 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/16 12:16:58 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	fill_sphere(t_sphere *sp, char **split)
{
	char	**coord;

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
	if (put_colors(&sp->color, split[3]))
		return (1);
	return (0);
}

int	fill_plane(t_plane *pl, char **split)
{
	char	**coord;
	char	**norm;

	if (ft_array_len(split) != 4)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3 || put_coord(&pl->coord, coord))
		return (ft_free_malloc_array(coord), 1);
	ft_free_malloc_array(coord);
	norm = ft_split(split[2], ',');
	if (!norm)
		return (1);
	if (ft_array_len(norm) != 3 || put_direct(&pl->direct, norm))
		return (ft_free_malloc_array(norm), 1);
	ft_free_malloc_array(norm);
	if (put_colors(&pl->color, split[3]))
		return (1);
	return (0);
}

int	fill_cylinder(t_cylinder *cy, char **split)
{
	char	**coord;
	char	**norm;

	if (ft_array_len(split) != 6)
		return (1);
	coord = ft_split(split[1], ',');
	if (!coord)
		return (1);
	if (ft_array_len(coord) != 3 || put_coord(&cy->coord, coord))
		return (ft_free_malloc_array(coord), 1);
	ft_free_malloc_array(coord);
	norm = ft_split(split[2], ',');
	if (!norm)
		return (1);
	if (ft_array_len(norm) != 3 || put_direct(&cy->direct, norm))
		return (ft_free_malloc_array(norm), 1);
	ft_free_malloc_array(norm);
	if (ft_test_double(split[3], 0, 1000) || ft_test_double(split[4], 0, 1000))
		return (1);
	cy->radius = ft_atod(split[3]) / 2;
	cy->height = ft_atod(split[4]);
	if (put_colors(&cy->color, split[5]))
		return (1);
	return (0);
}
