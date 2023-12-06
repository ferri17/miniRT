/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/06 11:47:59 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	add_vec3(const t_vec3 *vector1, const t_vec3 *vector2)
{
	t_vec3	res;

	res.x = vector1->x + vector2->x;
	res.y = vector1->y + vector2->y;
	res.z = vector1->z + vector2->z;
	return (res);
}

t_vec3	substract_vec3(const t_vec3 *vector1, const t_vec3 *vector2)
{
	t_vec3	res;

	res.x = vector1->x - vector2->x;
	res.y = vector1->y - vector2->y;
	res.z = vector1->z - vector2->z;
	return (res);
}

void	product_vec3(t_vec3 *vector, double factor)
{
	vector->x *= factor;
	vector->y *= factor;
	vector->z *= factor;
}

void	division_vec3(t_vec3 *vector, double factor)
{
	vector->x /= factor;
	vector->y /= factor;
	vector->z /= factor;
}

double	dot(const t_vec3 *v1, const t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
