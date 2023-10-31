/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:46:08 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 21:20:33 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_digits_unsigned(unsigned int nb, int printed)
{
	int	remainder;

	if (nb > 0)
	{
		remainder = nb % 10;
		printed = ft_print_digits_unsigned(nb / 10, printed);
		if (printed < 0)
			return (-1);
		if (ft_print_char('0' + remainder) < 0)
			return (-1);
		printed++;
	}
	return (printed);
}

int	ft_print_unsigned(unsigned int nb)
{
	int	printed;

	printed = 0;
	if (nb != 0)
		printed = ft_print_digits_unsigned(nb, printed);
	else
		printed = ft_print_char('0');
	return (printed);
}
