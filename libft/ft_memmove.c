/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:31:45 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/06 00:19:04 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*original_dst;
	unsigned char		*original_src;

	original_dst = (unsigned char *) dst;
	original_src = (unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	if (original_dst > original_src)
	{
		while (len--)
			*(original_dst + len) = *(original_src + len);
	}
	else
	{
		while (len--)
			*original_dst++ = *original_src++;
	}
	return (dst);
}
