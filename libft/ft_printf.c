/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:59:40 by fbosch            #+#    #+#             */
/*   Updated: 2023/09/25 00:57:29 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_arguments(va_list args, char c)
{
	unsigned int	printed;

	printed = 0;
	if (c == 'c')
		printed = ft_print_char(va_arg(args, int));
	else if (c == 's')
		printed = ft_print_string(va_arg(args, char *));
	else if (c == 'p')
		printed = ft_print_pointer(va_arg(args, unsigned long));
	else if (c == 'i' || c == 'd')
		printed = ft_print_integer_signed(va_arg(args, int));
	else if (c == 'u')
		printed = ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		printed = ft_print_hexa(va_arg(args, unsigned int), 0);
	else if (c == 'X')
		printed = ft_print_hexa(va_arg(args, unsigned int), 1);
	else if (c == '%')
		printed = ft_print_char('%');
	else
		printed = ft_print_char(c);
	return (printed);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	int				printed;
	int				temp;
	int				i;

	va_start(args, str);
	printed = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			temp = print_arguments(args, str[i + 1]);
			i++;
		}
		else
			temp = ft_print_char(str[i]);
		if (temp < 0)
			return (-1);
		printed += temp;
		i++;
	}
	va_end(args);
	return (printed);
}
