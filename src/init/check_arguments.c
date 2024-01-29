/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:32 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/28 11:44:29 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

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

void	print_error_line(char **split, int fd, char *line)
{
	ft_free_malloc_array(split);
	close(fd);
	ft_printf_fd(STDERR_FILENO, line);
	ft_printf_fd(STDERR_FILENO, "\n");
	free(line);
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
			return (free(line), close(fd), 1);
		if (check_ident(scene, split))
			return (print_error_line(split, fd, line), 1);
		free(line);
		ft_free_malloc_array(split);
		line = get_next_line(fd);
	}
	close(fd);
	if (scene->camera.init == false || scene->amblight.init == false)
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
		if (compare_str_end(filename, ".rt") != 0)
			return (ft_printf_fd(STDERR_FILENO, ERR_MISSING_RT_EXTENSION), 1);
		fd = open(filename, O_RDONLY);
		close(fd);
		if (fd == -1)
			return (ft_printf_fd(STDERR_FILENO, ERR_OPENING_MAP), 1);
		if (IMG_W < 200 || IMG_H < 200 || IMG_W > 1500 || IMG_H > 1500)
			return (ft_printf_fd(STDERR_FILENO, ERR_CANVAS_SIZE), 1);
	}
	else
		return (ft_printf_fd(STDERR_FILENO, ERR_NO_MAP), 1);
	return (0);
}
