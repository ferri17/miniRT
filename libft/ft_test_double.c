/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:48:51 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/15 17:52:06 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	is_negative(char *str)
{
	if (*str == '-')
		return (-1);
	return (1);
}

int	is_valid_double(const char *str)
{
	int	point;

	point = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str == '.')
		{
			if (point)
				return (0);
			point = 1;
		}
		else if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

static int	testing_double(char *str, double min, double max, double sign)
{
	double	res;
	double	divisor;

	res = 0.0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.' && (res * sign >= min && res * sign <= max))
	{
		str++;
		divisor = 10.0;
		while (*str >= '0' && *str <= '9')
		{
			res += (*str - '0') / divisor;
			divisor *= 10.0;
			str++;
		}
	}
	res *= sign;
	if (res < min || res > max || *str != '\0')
		return (1);
	return (0);
}

int	ft_test_double(char *str, double min, double max)
{
	double	result;
	double	sign;

	result = 0.0;
	sign = is_negative(str);
	if (is_valid_double(str))
		return (1);
	if (sign == -1)
		str++;
	if (testing_double(str, min, max, sign))
		return (1);
	return (0);
}
