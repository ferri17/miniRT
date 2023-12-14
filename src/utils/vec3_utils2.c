/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/07 16:41:36 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	product_vec3_r(const t_vec3 *vector, double factor)
{
	t_vec3	res;

	res = *vector;
	res.x *= factor;
	res.y *= factor;
	res.z *= factor;
	return (res);
}

t_vec3	division_vec3_r(const t_vec3 *vector, double factor)
{
	t_vec3	res;

	res = *vector;
	res.x /= factor;
	res.y /= factor;
	res.z /= factor;
	return (res);
}

t_vec3	cross(const t_vec3 *v1, const t_vec3 *v2)
{
	t_vec3	res;

	res.x = v1->y * v2->z - v1->z * v2->y;
	res.y = v1->z * v2->x - v1->x * v2->z;
	res.z = v1->x * v2->y - v1->y * v2->x;
	return (res);
}

double	length(const t_vec3 *vector)
{
	return (sqrt(length_squared(vector)));
}

double	length_squared(const t_vec3 *vector)
{
	return (vector->x * vector->x
		+ vector->y * vector->y
		+ vector->z * vector->z);
}
