/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:32 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/22 12:50:02 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_ident(t_scene *scene, char **split)
{
	int	out;

	if (!split[0])
		return (0);
	out = 0;
	if (ft_strcmp(split[0], AMBIENT) == 0 && scene->ambligth.init == false)
		out = fill_ambient(scene, split);
	else if (ft_strcmp(split[0], CAMERA) == 0 && scene->camera.init == false)
		out = fill_camera(scene, split);
	else if (ft_strcmp(split[0], LIGHT) == 0)
		out = check_ligth(scene, split);
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

int	init_map(char *file, t_scene *scene)
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
			return (free(line), 1);        // Si t_scene fa algun malloc() aixo podria tenir leaks (no ho se si en te)
		free(line);
		if (check_ident(scene, split))
			return (ft_free_malloc_array(split), 1);
		ft_free_malloc_array(split);
		line = get_next_line(fd);
	}
	close(fd);
	if (scene->camera.init == false || scene->ambligth.init == false)
		return (1);
	return (0);
}

int	compare_str_end(char *str, char *end)
{
	int	len_str;
	int	len_end;

	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	return (ft_strcmp(str + len_str - len_end, end));
}

int	check_args(int argc, char **argv)
{
	char	*filename;
	int		fd;

	filename = argv[1];
	if (argc == 2)
	{
		fd = open(filename, O_RDONLY);
		close(fd);
		if (fd == -1)
		{
			ft_printf_fd(STDERR_FILENO, ERR_OPENING_MAP);
			return (1);
		}
		if (compare_str_end(filename, ".rt") != 0)
		{
			ft_printf_fd(STDERR_FILENO, ERR_MISSING_RT_EXTENSION);
			return (1);
		}
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, ERR_NO_MAP);
		return (1);
	}
	return (0);
}
