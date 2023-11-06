/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:32 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/06 19:33:39 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int check_args(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_strlen(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))) != 3)
		{
			ft_printf("Can only read .rt files");
			return (1);
		}
	}
	else
	{
		ft_printf("Please give me a .rt scene file");
		return (1);
	}
	return (0);
}
