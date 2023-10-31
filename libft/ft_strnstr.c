/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:11:20 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/07 01:17:21 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	len_needle = ft_strlen(needle);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, len_needle) == 0
				&& i + len_needle <= len)
				return ((char *) haystack + i);
		}
		i++;
	}
	return (NULL);
}
