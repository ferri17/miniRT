/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_uv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:06:24 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/09 15:16:19 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniRT.h>

t_uv get_planar_map(t_point3 *p_hit, t_point3 *dir, t_point3 *center)
{
	t_uv uv;
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

void coordinate_system(t_vec3 *c, t_vec3 *a, t_vec3 *b)
{
    // Asegurar que c es un vector unitario
    t_vec3 normalized_c = unit_vector(c);

    // Encontrar un vector a que sea perpendicular a c
    if (fabs(normalized_c.x) > 0.9)
        a->x = 0.0;
    else
        a->x = 1.0;
    a->x = normalized_c.y;
    a->y = normalized_c.z;
    a->z = -normalized_c.x;

    // Calcular el vector b como el producto cruz entre c y a
    *b = cross(&normalized_c, a);
}

double	ft_limit_cyl_height(double height, const double h)
{
	const double	min_height = -0.999 * h / 2.0;
	const double	max_height = 0.999 * h / 2.0;

	if (height < min_height)
		return (min_height);
	if (height > max_height)
		return (max_height);
	return (height);
}

t_uv get_cylinder_map(t_point3 *p_hit, t_vec3 *dir, t_point3 *base, double h)
{
	t_point3	center;
	t_uv		uv;
	t_ray	ray;

	ray.dir = *dir;
	ray.orig = *base;
	
	center = ray_at(&ray, h / 2);
	double theta = atan2(p_hit->x - center.x, p_hit->z - center.z);
	double phi = (p_hit->y - center.y) / h;
	uv.u = theta / (2.0 * M_PI);
    uv.v = (phi / M_PI);
    return (uv);
}

t_uv get_cone_map(t_point3 p_hit)
{
    t_uv uv;
    double theta = atan2(p_hit.x, p_hit.z);
    //double radius = p_hit.x * p_hit.x + p_hit.z * p_hit.z;
    double height = p_hit.y;

    // Mapeo de coordenada u
    uv.u = theta;

    // Mapeo de coordenada v usando la altura en lugar del radio
    uv.v = fmod(height, 1.0);

    return uv;
}
