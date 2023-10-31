/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:44:59 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 21:22:19 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (write (1, str, i) < 0)
		return (-1);
	return (i);
}

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_string(char *str)
{
	int	printed;

	if (str == NULL)
	{
		if (ft_putstr("(null)") < 0)
			return (-1);
		return (6);
	}
	printed = 0;
	while (str[printed])
		printed++;
	if (write (1, str, printed) < 0)
		return (-1);
	return (printed);
}
