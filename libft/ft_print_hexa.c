/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:55:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 21:23:56 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_numbers(unsigned int nb, int is_upper,
										const char *base, int printed)
{
	unsigned int	print;

	if (nb > 0)
	{
		print = nb % 16;
		printed = ft_print_numbers(nb / 16, is_upper, base, printed);
		if (printed < 0)
			return (-1);
		if (is_upper == 1 && base[print] >= 'a' && base[print] <= 'z')
		{
			if (ft_print_char(base[print] - 32) < 0)
				return (-1);
		}
		else
		{
			if (ft_print_char(base[print]) < 0)
				return (-1);
		}
		printed ++;
	}
	return (printed);
}

int	ft_print_hexa(unsigned int nb, int is_upper)
{
	const char		*base;
	unsigned int	printed;

	if (nb == 0)
	{
		return (ft_print_char('0'));
	}
	printed = 0;
	base = "0123456789abcdef";
	printed = ft_print_numbers(nb, is_upper, base, printed);
	return (printed);
}
