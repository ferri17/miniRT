/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:25:03 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/27 17:57:09 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_point3 ray_at(const t_ray *ray, double t)
{
	t_vec3		dir;

	dir = ray->dir;
	product_vec3(&dir, t);
	return (add_vec3(&ray->orig, &dir));
}
