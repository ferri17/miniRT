/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:48:51 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/19 17:14:34 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	add_decimals_number(char *str, double *res)
{
	double	decimal;
	int		i;
	double	div;

	decimal = 0;
	div = 10;
	i = 0;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]) && i < 10)
	{
		decimal = decimal + ((str[i] - '0') / div);
		div *= 10;
		i++;
	}
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (1);
	*res += decimal;
	return (0);
}

int	test_limits_number(char *str, double sign, double min, double max)
{
	int		i;
	double	res;
	double	tmp;

	res = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		tmp = res * sign;
		if (tmp > INT_MAX || tmp < INT_MIN)
			return (1);
		i++;
	}
	if (str[i] != '.' && str[i] != '\0')
		return (1);
	if (add_decimals_number(&str[i], &res) == 1)
		return (1);
	tmp = res * sign;
	if (tmp < min || tmp > max)
		return (1);
	return (0);
}

int	ft_test_double(char *str, double min, double max)
{
	int		i;
	double	sign;

	i = 0;
	if (!str)
		return (1);
	if (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+')
	{
		sign = 1;
		if (str[i] == '-')
		{
			sign = -1;
			i++;
		}
		else if (str[i] == '+')
			i++;
		if (test_limits_number(&str[i], sign, min, max))
			return (1);
	}
	else
		return (1);
	return (0);
}
