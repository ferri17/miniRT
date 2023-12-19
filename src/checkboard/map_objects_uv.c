/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_uv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:06:24 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/19 01:06:20 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniRT.h>

t_uv get_planar_map(t_point3 p_hit)
{
    t_uv uv;
	double	y;
    // Definir el tamaño de cada cuadrado en el patrón de ajedrez
    float squareSize = 1.0 / 3.0;

    // Calcular las coordenadas UV basadas en la posición relativa dentro del plano
    uv.u = fmod(p_hit.x / squareSize, 2.0);
    uv.v = fmod(p_hit.z / squareSize, 2.0);

    // Asegurar que las coordenadas estén en el rango [0, 1)
    if (uv.u < 0) uv.u += 2.0;
    if (uv.v < 0) uv.v += 2.0;

	y = p_hit.y;
	if (p_hit.y < 0)
		y *= -1;
    // Ajuste adicional para manejar la coordenada y
    uv.u = fmod(uv.u + fabs(y / squareSize), 1.0);
    uv.v = fmod(uv.v + fabs(y / squareSize), 1.0);

    return uv;
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
    double radius = p_hit.x * p_hit.x + p_hit.z * p_hit.z;
    double height = p_hit.y;

    // Mapeo de coordenada u
    uv.u = fmod(1 - ((theta / (2 * M_PI)) + 0.5), 1.0);

    // Mapeo de coordenada v usando la altura en lugar del radio
    uv.v = fmod(height, 1.0);

    return uv;
}
