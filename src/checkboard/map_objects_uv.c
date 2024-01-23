/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_uv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:06:24 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/23 13:46:09 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniRT.h>

t_uv	get_planar_map(t_point3 *p_hit, t_point3 *dir, t_point3 *center)
{
	t_uv	uv;
	t_vec3	tmp;
	t_vec3	axis;
	t_vec3	tmp1;
	t_vec3	tmp2;

	tmp = substract_vec3(p_hit, center);
	axis = (t_vec3){0.0, 0.0, 1.0};
	if (fabs(dot(dir, &axis)) > 0.95)
		axis = (t_vec3){1.0, 0.0, 0.0};
	tmp1 = cross(dir, &axis);
	tmp1 = unit_vector(&tmp1);
	tmp2 = cross(dir, &tmp1);
	uv.u = dot(&tmp1, &tmp);
	uv.v = dot(&tmp2, &tmp);
	return (uv);
}

t_uv	get_spherical_map(t_point3 *p_hit, t_point3 *center, double radius)
{
	t_uv	uv;
	double	theta;
	double	phi;

	theta = atan2(p_hit->x - center->x, p_hit->z - center->z);
	phi = acos((p_hit->y - center->y) / radius);
	uv.u = theta / (2.0 * M_PI);
	uv.v = (phi / M_PI);
	return (uv);
}

t_uv	get_cylinder_map(t_point3 *p_hit, t_point3 *center, double radius)
{
	t_uv		uv;
	double		phi;
	double		theta;

	theta = atan2(p_hit->x - center->x, p_hit->z - center->z);
	phi = (p_hit->y - center->y) / radius;
	uv.u = theta / (2.0 * M_PI);
	uv.v = (phi / M_PI);
	return (uv);
}

t_uv	get_cone_map(t_point3 p_hit)
{
	t_uv	uv;
	double	theta;

	theta = atan2(p_hit.x, p_hit.z);
	uv.u = theta;
	uv.v = fmod(p_hit.y, 1.0);
	return (uv);
}
