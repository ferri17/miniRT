/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_uv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:06:24 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/16 13:12:13 by apriego-         ###   ########.fr       */
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

double calcularAnguloDeRotacion(t_vec3 v) {
    // Vector objetivo [0, 1, 0]
    t_vec3 objetivo = {0, 1, 0};

    // Normalizar los vectores
    v = unit_vector(&v);
    objetivo = unit_vector(&objetivo);

    // Calcular el producto punto para encontrar el coseno del ángulo
    double cosenoAngulo = v.x * objetivo.x + v.y * objetivo.y + v.z * objetivo.z;

    // Calcular el ángulo en radianes
    double angulo = acos(cosenoAngulo);

    return angulo;
}

t_vec3 rotarPuntoEjeX(t_vec3 punto, double angulo) {
    double cosTheta = cos(angulo);
    double sinTheta = sin(angulo);

    t_vec3 resultado;
    resultado.x = punto.x;
    resultado.y = cosTheta * punto.y - sinTheta * punto.z;
    resultado.z = sinTheta * punto.y + cosTheta * punto.z;

    return resultado;
}

t_point3 normalizar(t_point3 v) {
    double magnitud = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (t_point3){v.x / magnitud, v.y / magnitud, v.z / magnitud};
}

t_vec3 rotarVector(t_vec3 v, t_vec3 axis, double angle) {
    t_vec3 result;
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    result.x = cosTheta * v.x + (1 - cosTheta) * (axis.x * axis.x * v.x + axis.x * axis.y * v.y + axis.x * axis.z * v.z) + sinTheta * (axis.y * v.z - axis.z * v.y);
    result.y = cosTheta * v.y + (1 - cosTheta) * (axis.x * axis.y * v.x + axis.y * axis.y * v.y + axis.y * axis.z * v.z) + sinTheta * (axis.z * v.x - axis.x * v.z);
    result.z = cosTheta * v.z + (1 - cosTheta) * (axis.x * axis.z * v.x + axis.y * axis.z * v.y + axis.z * axis.z * v.z) + sinTheta * (axis.x * v.y - axis.y * v.x);

    return result;
}


void	rotation(t_point3 *coord, t_point3 *angles)
{
	float	temp;



	temp = coord->y;
	coord->y = coord->y * cos(angles->x) - sin (angles->x) * coord->z;
	coord->z = temp * sin(angles->x) + cos(angles->x) * coord->z;
	temp = coord->x;
	coord->x = coord->x * cos(angles->y) + sin(angles->y) * coord->z;
	coord->z = -temp * sin(angles->y) + coord->z * cos(angles->y);
	temp = coord->x;
	coord->x = coord->x * cos(angles->z) - coord->y * sin(angles->z);
	coord->y = temp * sin(angles->z) + cos(angles->z) * coord->y;
}

void rotateYInverse(double angle, double input[3], double output[3]) {
    double cosTheta = cos(-angle); // Rotación inversa
    double sinTheta = sin(-angle);

    output[0] = cosTheta * input[0] + sinTheta * input[2];
    output[1] = input[1];
    output[2] = -sinTheta * input[0] + cosTheta * input[2];
}

t_uv get_cylinder_map(t_point3 *p_hit, t_vec3 *dir, t_point3 *base, double h)
{
	t_point3	center;
	t_uv		uv;
	t_ray       ray;

	ray.dir = *dir;
	ray.orig = *base;

	center = ray_at(&ray, h / 2);
	double theta = atan2(p_hit->x - center.x, p_hit->z - center.z);
	uv.u = theta / (2.0 * M_PI);
    uv.u = fmod(1 - (uv.u + 0.5) * 2, 1.0);
    uv.v = fmod((p_hit->y - center.y) * 2, 1);
    if (uv.v < 0) {
        uv.v += 1.0;
    }
    uv.v = fmod(uv.v * 8.0, 1.0);
    double direction[3] = {p_hit->x - center.x, p_hit->y - center.y, p_hit->z - center.z};
    double length = sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);
    double normalizedDirection[3] = {direction[0] / length, direction[1] / length, direction[2] / length};

    double angleY = atan2(normalizedDirection[0], normalizedDirection[2]);

    double rotatedUV[2] = {uv.u, uv.v};
    rotateYInverse(angleY, rotatedUV, rotatedUV);

    uv.u = rotatedUV[0];
    uv.v = rotatedUV[1];
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
