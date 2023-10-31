/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:35:59 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/07 16:49:14 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	str_len;
	size_t	i;
	size_t	j;
	size_t	k;

	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	i = 0;
	while (s[start + i] && len - i)
		i++;
	substr = malloc(sizeof(char) * (i + 1));
	if (substr == NULL)
		return (NULL);
	j = start;
	k = 0;
	while (i--)
		substr[k++] = s[j++];
	substr[k] = '\0';
	return (substr);
}
