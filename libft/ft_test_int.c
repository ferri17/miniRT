/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:32:23 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/13 12:39:39 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_test_int(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	i = ft_isspace(str);
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (-1);
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (0);
}
