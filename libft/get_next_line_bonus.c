/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:10:49 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 20:51:13 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	load_buffer(char *buffer, int fd)
{
	int	r_bytes;
	int	i;

	r_bytes = read (fd, buffer, BUFFER_SIZE);
	if (r_bytes < 0)
		return (-1);
	buffer[r_bytes] = '\0';
	if (r_bytes == 0)
		return (0);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static char	*read_file(int fd, char *remainder)
{
	char	*buffer;
	int		buff_status;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
	{
		free (remainder);
		return (NULL);
	}
	buff_status = 1;
	while (buff_status == 1)
	{
		buff_status = load_buffer(buffer, fd);
		if (buff_status < 0)
		{
			free (buffer);
			free (remainder);
			return (NULL);
		}
		if (*buffer)
			remainder = ft_strjoin_gnl(remainder, buffer);
	}
	free (buffer);
	return (remainder);
}

static char	*find_line(char *remainder)
{
	char	*line;
	int		i;
	int		size;

	if (!*remainder)
		return (NULL);
	i = 0;
	while (remainder[i] != '\n' && remainder[i] != '\0')
		i++;
	if (remainder[i] == '\n')
		size = i + 2;
	else
		size = i + 1;
	line = (char *)malloc(sizeof(char) * size);
	if (line == NULL)
		return (NULL);
	ft_strlcpy_gnl(line, remainder, size);
	return (line);
}

static char	*find_new_remainder(char *remainder)
{
	char	*new_remainder;
	int		i;
	int		size_new_rem;

	if (!*remainder)
		return (NULL);
	i = 0;
	while (remainder[i] != '\n' && remainder[i] != '\0')
		i++;
	if (remainder[i] == '\n')
	{
		size_new_rem = ft_strlen_gnl(remainder) - i;
		new_remainder = (char *)malloc(sizeof(char) * size_new_rem);
		if (new_remainder == NULL)
		{
			free (remainder);
			return (NULL);
		}
		ft_strlcpy_gnl(new_remainder, remainder + i + 1, size_new_rem);
	}
	else
		new_remainder = NULL;
	free (remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[OPEN_MAX] = {NULL};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder[fd] = read_file(fd, remainder[fd]);
	if (remainder[fd] == NULL)
		return (NULL);
	line = find_line(remainder[fd]);
	if (line == NULL)
	{
		free (remainder[fd]);
		remainder[fd] = NULL;
	}
	else
		remainder[fd] = find_new_remainder(remainder[fd]);
	return (line);
}

/*#include <fcntl.h>
int main(void)
{
	int fd;
	char *line;

	fd = open("fd.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("Line: %s\n", line);
	line = get_next_line(fd);
	printf("Line: %s\n", line);
	free(line);

	line = get_next_line(fd);
	printf("Line: %s\n", line);
	line = get_next_line(fd);
	printf("Line: %s\n", line);
	line = get_next_line(fd);
	printf("Line: %s\n", line);
	line = get_next_line(fd);
	printf("Line: %s\n", line);
	line = get_next_line(fd);
	printf("Line: %s\n", line);
}*/
