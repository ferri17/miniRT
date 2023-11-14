/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:42:57 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/14 12:43:09 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	put_colors(t_colors *colors, char *split)
{
	int		gradient;
	char	**s_colors;

	s_colors = ft_split(split, ',');
	if (!s_colors)
		return (1);
	if (ft_array_len(s_colors) != 3)
		return (ft_free_malloc_array(s_colors), 1);
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
