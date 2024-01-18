/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 02:36:21 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/18 13:25:42 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	close_program(t_scene *scene, int exit_code)
{
	free_structs(*scene);
	mlx_destroy_image(scene->data.mlx, scene->data.img.ptr);
	mlx_destroy_window(scene->data.mlx, scene->data.mlx_win);
	mlx_destroy(scene->data.mlx);
	exit(exit_code);
}
void	check_limits_move(double *nb, double move)
{
	*nb += move;
	if (*nb > INT_MAX)
		*nb = INT_MAX;
	else if (*nb < INT_MIN)
		*nb = INT_MIN;
}

void	move_object(t_scene *scene, int key)
{
	t_vec3	*vector;

	if (scene->selected == NULL)
		return ;
	vector = scene->selected->get_position_pointer(&scene->selected->type);
	if (key == A_KEY)
		check_limits_move(&vector->x, -MOVE);
	else if (key == D_KEY)
		check_limits_move(&vector->x, MOVE);
	else if (key == W_KEY)
		check_limits_move(&vector->y, MOVE);
	else if (key == S_KEY)
		check_limits_move(&vector->y, -MOVE);
	else if (key == ONE_KEY)
		check_limits_move(&vector->z, MOVE);
	else if (key == TWO_KEY)
		check_limits_move(&vector->z, -MOVE);
}
