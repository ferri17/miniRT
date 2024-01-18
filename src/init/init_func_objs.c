/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func_objs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:18:20 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/18 13:28:39 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_dir(t_vec3 *dir)
{
	if (dir->x == 0 && dir->y == 0 && dir->z == 0)
		return (1);
	return (0);
}

void	inti_func_cylinder(t_world *cy)
{
	t_ray	ray;

	cy->type.cy->dir = unit_vector(&cy->type.cy->dir);
	ray.dir = cy->type.cy->dir;
	ray.orig = cy->type.cy->center;
	cy->type.cy->center = ray_at(&ray, -(cy->type.cy->height / 2));
	cy->hit = hit_cylinder;
	cy->get_position_pointer = get_position_cylinder;
	cy->get_color = get_color_cylinder;
}

void	inti_func_cone(t_world *cn)
{
	cn->type.cn->angle = deg_to_rad(cn->type.cn->angle);
	cn->type.cn->dir = unit_vector(&cn->type.cn->dir);
	cn->hit = hit_disk_cone;
	cn->get_position_pointer = get_position_cone;
	cn->get_color = get_color_cone;
}
