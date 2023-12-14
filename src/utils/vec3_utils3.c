/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:41:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/07 17:42:45 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3	unit_vector(const t_vec3 *vector)
{
	return (division_vec3_r(vector, length(vector)));
}

t_vec3	normal_vector(t_vec3 *vector, double old_range, double new_range)
{
	t_vec3	normalized;

	normalized = product_vec3_r(vector, new_range);
	normalized = division_vec3_r(&normalized, old_range);
	return (normalized);
}

t_vec3	vproduct_vec3(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	result;

	result.x = v1->x * v2->x;
	result.y = v1->y * v2->y;
	result.z = v1->z * v2->z;
	return (result);
}

