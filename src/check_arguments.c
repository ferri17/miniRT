/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:32 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/09 12:31:32 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_ident(t_scene *scene, char **split)
{

	if (ft_strcmp(split[0], AMBIENT))
		fill_ambient(scene, split);
	else if (ft_strcmp(split[0], CAMERA))
		fill_camera(scene, split);
	else if (ft_strcmp(split[0], LIGHT))
		fill_light(scene, split);
	else if (ft_strcmp(split[0], SPHERE))
		fill_sphere(scene, split);
	else if (ft_strcmp(split[0], PLANE))
		fill_plane(scene, split);
	else if (ft_strcmp(split[0], CYLINDER))
		fill_cylinder(scene, split);
	else
		return (1);
	return (0);
}

int	check_map(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		if (!split)
			return (free(line), 1);
		check_ident(scene, split);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_strlen(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))) != 3)
		{
			ft_printf("Can only read .rt files");
			return (1);
		}
	}
	else
	{
		ft_printf("Please give me a .rt scene file");
		return (1);
	}
	return (0);
}
