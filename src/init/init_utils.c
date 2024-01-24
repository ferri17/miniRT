/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:18:04 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/24 12:18:36 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_materia(t_world *obj, char **split, int pos)
{
	if (ft_test_double(split[pos], 0.0, 1.0))
		return (1);
	if (ft_test_double(split[pos + 1], 2.0, 256.0))
		return (1);
	if (ft_test_double(split[pos + 2], 0.0, 1.0))
		return (1);
	obj->materia.specular = ft_atod(split[pos]);
	obj->materia.roughness = ft_atod(split[pos + 1]);
	obj->materia.metallic = ft_atod(split[pos + 2]);
	return (0);
}
