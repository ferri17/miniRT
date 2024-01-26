/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_uv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:48 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/26 15:54:32 by apriego-         ###   ########.fr       */
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
	uv.u = 1 + (uv.u * -1.0);
	uv.v = 1 + (uv.v * -1.0);
	return (uv);
}

t_uv	get_spherical_map(t_point3 *p_hit, t_point3 *center, double radius)
{
	t_uv	uv;
	double	theta;
	double	phi;

	theta = atan2(p_hit->z - center->z, p_hit->x - center->x);
	phi = asin((p_hit->y - center->y) / radius);
	uv.u = 0.5 + (theta / (2.0 * M_PI));
	uv.v = 0.5 + (phi / M_PI);
	uv.u = 1 + (uv.u * -1.0);
	uv.v = 1 + (uv.v * -1.0);
	return (uv);
}

t_uv	get_cylinder_map(t_point3 *p_hit, t_point3 *center, double radius)
{
	t_uv	uv;
	double	phi;
	double	theta;

	theta = atan2(p_hit->z - center->z, p_hit->x - center->x);
	phi = (p_hit->y - center->y) / radius;
	uv.u = 0.5 + (theta / (2.0 * M_PI));
	uv.v = 0.5 + (phi / M_PI);
	uv.u = 1 + (uv.u * -1.0);
	uv.v = 1 + (uv.v * -1.0);
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
