/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:11:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/24 10:32:08 by fbosch           ###   ########.fr       */
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

int	clamp_number(int nb, int low_limit, int high_limit)
{
	if (nb < low_limit)
		nb = low_limit;
	else if (nb > high_limit)
		nb = high_limit;
	return (nb);
}