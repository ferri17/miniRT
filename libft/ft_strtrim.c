/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:50:22 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/10 21:11:30 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set_char(char const c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	i;
	size_t	len;
	size_t	trim_end;

	if (!*s1)
		return (ft_strdup(""));
	while (is_set_char(*s1, set) == 1 && *s1)
		s1++;
	len = ft_strlen(s1);
	trim_end = 0;
	while (is_set_char(s1[len - 1 - trim_end], set) == 1 && trim_end < len)
		trim_end++;
	strtrim = malloc(sizeof(char) * len - trim_end + 1);
	if (strtrim == NULL)
		return (NULL);
	i = 0;
	while (i < len - trim_end)
	{
		strtrim[i] = s1[i];
		i++;
	}
	strtrim[i] = '\0';
	return (strtrim);
}
