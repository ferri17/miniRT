/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_uv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:06:24 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/19 15:36:07 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniRT.h>

t_uv get_planar_map(t_point3 *p_hit, t_point3 *dir)
{
	t_uv uv;
	// Definir el tamaño de cada cuadrado en el patrón de ajedrez
	float squareSize = 1.0 / 3.0;
	if (dir->x != 0)
	{
		uv.u = fmod(p_hit->z / squareSize, 1.0);
		uv.v = fmod(p_hit->y / squareSize, 1.0);
	}
	else if (dir->y != 0)
	{
		uv.u = fmod(p_hit->z / squareSize, 1.0);
		uv.v = fmod(p_hit->x / squareSize, 1.0);
	}
	else
	{
		uv.u = fmod(p_hit->y / squareSize, 1.0);
		uv.v = fmod(p_hit->x / squareSize, 1.0);
	}
	return (uv);
}

t_uv	get_spherical_map(t_point3 p_hit)
{
	t_uv	uv;
	double	theta;
	double	phi;

	theta = acos(-p_hit.y);
	phi = atan2(-p_hit.z, p_hit.x) + M_PI;
    uv.u = fmod(1 - ((theta / (2 * M_PI)) + 0.5), 1.0);
    uv.v = fmod(1 - (phi / M_PI), 1.0);
	return (uv);
}

t_uv	get_cylinder_map(t_point3 p_hit)
{
	t_uv	uv;
	double	theta;

	theta = atan2(p_hit.x, p_hit.z);
	uv.u = fmod(1 - ((theta / (2 * M_PI)) + 0.5), 1.0);
	uv.v = fmod(p_hit.y, 1);
	return (uv);
}

t_uv get_cone_map(t_point3 p_hit)
{
    t_uv uv;
    double theta = atan2(p_hit.x, p_hit.z);
    //double radius = p_hit.x * p_hit.x + p_hit.z * p_hit.z;
    double height = p_hit.y;

    // Mapeo de coordenada u
    uv.u = fmod(1 - ((theta / (2 * M_PI)) + 0.5), 1.0);

    // Mapeo de coordenada v usando la altura en lugar del radio
    uv.v = fmod(height, 1.0);

    return uv;
}
