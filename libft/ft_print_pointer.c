/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:48:09 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 21:22:42 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_hexa_format(unsigned long ptr, const char *base,
											unsigned int printed)
{
	int	print;

	if (ptr > 0)
	{
		print = ptr % 16;
		printed = ft_print_hexa_format(ptr / 16, base, printed);
		if (printed < 0)
			return (-1);
		if (ft_print_char(base[print]) < 0)
			return (-1);
		printed ++;
	}
	return (printed);
}

int	ft_print_pointer(unsigned long ptr)
{
	const char	*base;
	int			printed;

	if (ft_putstr("0x") < 0)
		return (-1);
	if (ptr == 0)
	{
		if (ft_print_char('0') < 0)
			return (-1);
		return (3);
	}
	printed = 0;
	base = "0123456789abcdef";
	printed = ft_print_hexa_format(ptr, base, printed);
	return (printed + 2);
}
