/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:03:04 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/12 10:41:44 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	number_length(int n)
{
	size_t	chars;

	chars = 0;
	if (n <= 0)
		chars++;
	while (n != 0)
	{
		n /= 10;
		chars++;
	}
	return (chars);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		remainder;
	size_t	i;

	i = number_length(n);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		remainder = n % 10;
		if (remainder < 0)
			remainder *= -1;
		*(str + i) = '0' + remainder;
		n /= 10;
		i--;
	}
	return (str);
}
