/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ident.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:09:18 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/29 13:01:41 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_ident(t_scene *scene, char **split)
{
	int	out;

	if (!split[0])
		return (0);
	out = 0;
	if (split[0][0] == '#')
		out = 0;
	else if (ft_strcmp(split[0], AMBIENT) == 0 && scene->amblight.init == false)
		out = fill_ambient(scene, split);
	else if (ft_strcmp(split[0], CAMERA) == 0 && scene->camera.init == false)
		out = fill_camera(scene, split);
	else if (ft_strcmp(split[0], LIGHT) == 0)
		out = check_light(scene, split);
	else if (ft_strcmp(split[0], SPHERE) == 0)
		out = check_sphere(scene, split);
	else if (ft_strcmp(split[0], PLANE) == 0)
		out = check_plane(scene, split);
	else if (ft_strcmp(split[0], CYLINDER) == 0)
		out = check_cylinder(scene, split);
	else if (ft_strcmp(split[0], CONE) == 0)
		out = check_cone(scene, split);
	else
		out = 1;
	return (out);
}
