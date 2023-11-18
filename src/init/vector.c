/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:17 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/16 12:35:21 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	add_vec3(t_vec3 *vector1, t_vec3 *vector2)
{
	t_vec3	res;

	res.e[X] = vector1->e[X] + vector2->e[X];
	res.e[Y] = vector1->e[Y] + vector2->e[Y];
	res.e[Z] = vector1->e[Z] + vector2->e[Z];
	return (res);
}

t_vec3	substract_vec3(t_vec3 *vector1, t_vec3 *vector2)
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
