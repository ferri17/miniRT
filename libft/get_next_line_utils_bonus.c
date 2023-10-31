/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:10:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 20:59:47 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*str;
	size_t	size;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup_gnl(s2));
	size = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
	{
		free (s1);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	if (s1)
		free (s1);
	return (str);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (!s1)
		return (NULL);
	size = ft_strlen_gnl(s1) + 1;
	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	if (dstsize != 0)
	{
		while (j < (dstsize - 1) && src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (i);
}
