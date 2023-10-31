/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:38:04 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/09 14:56:48 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_number(int n, int fd)
{
	int		remainder;
	char	print;

	if (n != 0)
	{
		remainder = n % 10;
		if (remainder < 0)
			remainder *= -1;
		print = '0' + remainder;
		print_number(n / 10, fd);
		write(fd, &print, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	else if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	print_number(n, fd);
}
