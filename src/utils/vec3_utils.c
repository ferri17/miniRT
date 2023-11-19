/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/19 22:51:32 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	add_vec3(const t_vec3 *vector1, const t_vec3 *vector2)
{
	t_vec3	res;

	res.e[X] = vector1->e[X] + vector2->e[X];
	res.e[Y] = vector1->e[Y] + vector2->e[Y];
	res.e[Z] = vector1->e[Z] + vector2->e[Z];
	return (res);
}

t_vec3	substract_vec3(const t_vec3 *vector1, const t_vec3 *vector2)
{
	t_vec3	res;

	res.e[X] = vector1->e[X] - vector2->e[X];
	res.e[Y] = vector1->e[Y] - vector2->e[Y];
	res.e[Z] = vector1->e[Z] - vector2->e[Z];
	return (res);
}

void	product_vec3(t_vec3 *vector, double factor)
{
	vector->e[X] *= factor;
	vector->e[Y] *= factor;
	vector->e[Z] *= factor;
}

void	division_vec3(t_vec3 *vector, double factor)
{
	vector->e[X] /= factor;
	vector->e[Y] /= factor;
	vector->e[Z] /= factor;
}

double	dot(const t_vec3 *v1, const t_vec3 *v2)
{
	return (v1->e[X] * v2->e[X] + v1->e[Y] * v2->e[Y] + v1->e[Z] * v2->e[Z]);
}
