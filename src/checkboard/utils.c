/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:31:58 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/18 11:32:19 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

double	quit_decimals(double num)
{
	const double	ratio = (num * 5) / 2.0;

	return (ratio - floor(ratio));
}

t_color	checker_color(t_uv uv, t_color color)
{
	double	tmp1;
	double	tmp2;

	tmp1 = quit_decimals(uv.u);
	tmp2 = quit_decimals(uv.v);
	if ((tmp1 < 0.5) ^ (tmp2 < 0.5))
	{
		return (color);
	}
	else
	{
		return ((t_color){0.0f, 0.0f, 0.0f});
	}
}
