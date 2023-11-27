/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:46:29 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/26 16:22:16 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	close_program(t_scene *scene, int exit_code)
{
	mlx_destroy_window(scene->data.mlx, scene->data.mlx_win);
	mlx_destroy(scene->data.mlx);
	exit(exit_code);
}

int	key_down(int key, void *param)
{
	t_scene	*scene;
	scene = (t_scene *)param;
	if (key == ESC_KEY)
		close_program(scene, EXIT_SUCCESS);
	return (0);
}
