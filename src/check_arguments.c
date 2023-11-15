/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:32 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/15 18:13:01 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_ident(t_scene *scene, char **split)
{
	int	out;

	out = 0;
	if (!split[0])
		return (0);
	else if (ft_strcmp(split[0], AMBIENT) == 0)
		out = fill_ambient(scene, split);
	else if (ft_strcmp(split[0], CAMERA) == 0)
		out = fill_camera(scene, split);
	else if (ft_strcmp(split[0], LIGHT) == 0)
		out = fill_light(scene, split);
	else if (ft_strcmp(split[0], SPHERE) == 0)
		out = check_sphere(scene, split);
	else if (ft_strcmp(split[0], PLANE) == 0)
		out = check_plane(scene, split);
	else if (ft_strcmp(split[0], CYLINDER) == 0)
		out = check_cylinder(scene, split);
	else
		out = 1;
	return (out);
}

static char	*ft_purge_line(char *line)
{
	int	i;

	i = 0;
	if (ft_strchr(line, '\n'))
	{
		while (line[i] != '\n')
			i++;
		line[i] = '\0';
	}
	return (line);
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
		line = ft_purge_line(line);
		split = ft_split(line, ' ');
		if (!split)
			return (free(line), 1);
		free(line);
		if (check_ident(scene, split))
			return (ft_free_malloc_array(split), 1);
		ft_free_malloc_array(split);
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
