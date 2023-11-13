/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:08:50 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/13 11:48:37 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_negative(char *str)
{
	if (*str == '-')
		return (-1);
	return (1);
}

double	ft_atod(char *str)
{
	double	result;
	int		sign;
	double	divisor;

	result = 0.0;
	sign = is_negative(str);
	if (sign == -1)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		divisor = 10.0;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str - '0') / divisor;
			divisor *= 10.0;
			str++;
		}
	}
	return (sign * result);
}
