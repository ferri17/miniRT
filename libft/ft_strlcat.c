/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 00:30:12 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/12 15:00:30 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	total_len;

	i = 0;
	j = 0;
	total_len = 0;
	while (dst[i])
		i++;
	while (src[total_len])
		total_len++;
	if (dstsize <= i)
		total_len = total_len + dstsize;
	if (dstsize > i)
		total_len = total_len + i;
	while (src[j] && (i + 1) < dstsize)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (total_len);
}
