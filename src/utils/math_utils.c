/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:11:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/01 23:02:12 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	create_color(int a, int r, int g, int b)
{
	const int	min_channel = 0;
	const int	max_channel = 255;
	int	color;

	color = clamp_number(a, min_channel, max_channel);
	color = (color << 8) + clamp_number(r, min_channel, max_channel);
	color = (color << 8) + clamp_number(g, min_channel, max_channel);
	color = (color << 8) + clamp_number(b, min_channel, max_channel);
	return (color);
}

double	clamp_number(double nb, int low_limit, int high_limit)
{
	if (nb < (double)low_limit)
		nb = low_limit;
	else if (nb > (double)high_limit)
		nb = high_limit;
	return (nb);
}

double	deg_to_rad(double degree)
{
	return (degree * M_PI / 180.0);
}
