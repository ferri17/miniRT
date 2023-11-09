/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:49:05 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/09 15:45:02 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (check_args(argc, argv) == 1)
		return (1);
	scene = init_structs();
	if (check_map(argv[1], &scene))
	{
		ft_printf("SOY PRACTICAMENTE UN DIOS");
		return (1);
	}
	return (0);
}
