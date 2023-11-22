/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:25:03 by fbosch            #+#    #+#             */
/*   Updated: 2023/11/22 13:33:03 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_point3 at(t_ray *ray, double t)
{
	t_point3	at;
	t_vec3		dir;

	dir = ray->dir;
	product_vec3(&dir, t);
	return (add_vec3(&ray->orig, &dir));
}
