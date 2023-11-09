/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:24:41 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/09 15:47:31 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"


int	put_colors(t_colors *colors, char **s_colors)
{
	int	gradient;

	gradient = ft_atoi(s_colors[0]);
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

int	fill_ambient(t_scene *scene, char **split)
{
	double	ratio;
	char	**colors;

	if (ft_array_len(split) != 3)
		return (1);
	// if (ft_test_double(split[1]))
	// 	return (1);
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

// int	fill_camera(t_scene *scene, char **split)
// {

// }

// int	fill_light(t_scene *scene, char **split)
// {

// }

// int	fill_sphere(t_scene *scene, char **split)
// {

// }

// int	fill_plane(t_scene *scene, char **split)
// {

// }

// int	fill_cylinder(t_scene *scene, char **split)
// {

// }
