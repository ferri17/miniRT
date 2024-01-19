/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:12:30 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/19 12:13:14 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3	*get_position_sphere(t_objects *obj)
{
	return (&obj->sp->center);
}

t_vec3	*get_position_cylinder(t_objects *obj)
{
	return (&obj->cy->center);
}

t_vec3	*get_position_plane(t_objects *obj)
{
	return (&obj->pl->center);
}

t_vec3	*get_position_cone(t_objects *obj)
{
	return (&obj->cn->center);
}
