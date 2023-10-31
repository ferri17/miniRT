/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:04:16 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/05 01:30:13 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*original_dst;
	unsigned const char	*original_src;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	original_dst = (unsigned char *) dst;
	original_src = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		original_dst[i] = original_src[i];
		i++;
	}
	return (dst);
}
