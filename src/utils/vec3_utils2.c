/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/19 22:52:29 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	cross(const t_vec3 *v1, const t_vec3 *v2)
{
	t_vec3	res;

	res.e[X] = v1->e[Y] * v2->e[Z] - v1->e[Z] * v2->e[Y];
	res.e[Y] = v1->e[Z] * v2->e[X] - v1->e[X] * v2->e[Z];
	res.e[Z] = v1->e[X] * v2->e[Y] - v1->e[Y] * v2->e[X];
	return (res);
}

double	length(const t_vec3 *vector)
{
	return (sqrt(length_squared(vector)));
}

double	length_squared(const t_vec3 *vector)
{
	return (vector->e[X] * vector->e[X]
		+ vector->e[Y] * vector->e[Y]
		+ vector->e[Z] * vector->e[Z]);
}

t_vec3	unit_vector(const t_vec3 *vector)
{
	t_vec3	unit_vector;

	unit_vector = *vector;
	division_vec3(&unit_vector, length(&unit_vector));
	return (unit_vector);
}
