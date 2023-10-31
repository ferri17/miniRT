/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer_signed.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:47:10 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 21:23:08 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_digits_signed(int nb, int printed)
{
	int	remainder;

	if (nb != 0)
	{
		remainder = nb % 10;
		if (remainder < 0)
			remainder *= -1;
		printed = ft_print_digits_signed(nb / 10, printed);
		if (printed < 0)
			return (-1);
		if (ft_print_char('0' + remainder) < 0)
			return (-1);
		printed++;
	}
	return (printed);
}

int	ft_print_integer_signed(int nb)
{
	int	printed;

	printed = 0;
	if (nb < 0)
		printed = ft_print_char('-');
	else if (nb == 0)
		printed = ft_print_char('0');
	if (printed < 0)
		return (-1);
	printed = ft_print_digits_signed(nb, printed);
	return (printed);
}
