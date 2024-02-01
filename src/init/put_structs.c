/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:42:57 by apriego-          #+#    #+#             */
/*   Updated: 2024/02/01 17:54:56 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	put_colors(t_color *colors, char *split)
{
	int		gradient;
	char	**s_colors;

	s_colors = ft_split(split, ',');
	if (!s_colors)
		return (1);
	if (ft_array_len(s_colors) != 3)
		return (ft_free_malloc_array(s_colors), 1);
	gradient = ft_atoi(s_colors[0]);
	if (ft_test_int(s_colors[0]) == 0 && gradient < 256 && gradient >= 0)
		colors->x = gradient;
	else
		return (ft_free_malloc_array(s_colors), 1);
	gradient = ft_atoi(s_colors[1]);
	if (ft_test_int(s_colors[1]) == 0 && gradient < 256 && gradient >= 0)
		colors->y = gradient;
	else
		return (ft_free_malloc_array(s_colors), 1);
	gradient = ft_atoi(s_colors[2]);
	if (ft_test_int(s_colors[2]) == 0 && gradient < 256 && gradient >= 0)
		colors->z = gradient;
	else
		return (ft_free_malloc_array(s_colors), 1);
	*colors = normal_vector(colors, 255, 1);
	return (ft_free_malloc_array(s_colors), 0);
}

int	put_coord(t_point3 *coord, char **coords)
{
	if (ft_test_double(coords[0], INT_MIN, INT_MAX) == 0)
		coord->x = ft_atod(coords[0]);
	else
		return (1);
	if (ft_test_double(coords[1], INT_MIN, INT_MAX) == 0)
		coord->y = ft_atod(coords[1]);
	else
		return (1);
	if (ft_test_double(coords[2], INT_MIN, INT_MAX) == 0)
		coord->z = ft_atod(coords[2]);
	else
		return (1);
	return (0);
}

int	put_dir(t_vec3 *dir, char **norm)
{
	if (ft_test_double(norm[0], -1.0000, 1.0000) == 0)
		dir->x = ft_atod(norm[0]);
	else
		return (1);
	if (ft_test_double(norm[1], -1.0000, 1.0000) == 0)
		dir->y = ft_atod(norm[1]);
	else
		return (1);
	if (ft_test_double(norm[2], -1.0000, 1.0000) == 0)
		dir->z = ft_atod(norm[2]);
	else
		return (1);
	if (dir->x == 0 && dir->y == 0 && dir->z == 0)
		return (1);
	*dir = unit_vector(dir);
	return (0);
}

int	put_fov(int *hfov, char *num)
{
	int	number;

	number = ft_atoi(num);
	if (ft_test_int(num) == 0 && number >= 1 && number <= 179)
		*hfov = number;
	else
		return (1);
	return (0);
}
