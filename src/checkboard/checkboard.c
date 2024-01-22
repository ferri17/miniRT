/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:03:13 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/22 18:51:49 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

typedef struct s_matrix3x3{
    double m[3][3];
} t_matrix3x3;

t_color	get_color_sphere(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;

	if (objs->materia.texture == DEFAULT)
		return (objs->materia.color);
	uv = get_spherical_map(p_hit, &objs->type.sp->center,
			objs->type.sp->radius);
	uv.u *= 4;
	uv.v *= 2;
	return (checker_color(uv, objs->materia.color));
}

t_color	get_color_plane(t_vec3 *p_hit, t_world *objs)
{
	t_uv	uv;

	if (objs->materia.texture == DEFAULT)
		return (objs->materia.color);
	uv = get_planar_map(p_hit, &objs->type.pl->normal, &objs->type.pl->center);
	return (checker_color(uv, objs->materia.color));
}

t_color	get_color_cone(t_vec3 *p_hit, t_world *objs)
{
	t_color	color;
	t_uv	uv;

	if (objs->materia.texture == DEFAULT)
		return (objs->materia.color);
	if (objs->type.cn->hit[H_CONE])
	{
		uv = get_cylinder_map(p_hit, &objs->type.cn->center, objs->type.cn->height);
		uv.u *= 6;
		uv.v *= 2;
		return (checker_color(uv, objs->materia.color));
	}
	else
	{
		uv = get_planar_map(p_hit, &objs->type.cn->dir, &objs->type.pl->center);
		uv.u *= 6;
		uv.v *= 2;
		return (checker_color(uv, objs->materia.color));
	}
	return (color);
}

t_color	checker_color_cylinder(t_uv uv, t_color color)
{
	int	u_int;
	int	v_int;

	u_int = uv.u * 8;
	v_int = uv.v * 8;
	if (((u_int % 2) == 0) ^ ((v_int % 2) == 0))
		return (color);
	return ((t_color){0, 0, 0});
}

t_matrix3x3 calculateRotationMatrix(double angle, t_vec3 *axis) {
    double cosTheta = cos(angle);
    double sinTheta = sin(angle);

    t_matrix3x3 rotationMatrix;

    rotationMatrix.m[0][0] = cosTheta + axis->x * axis->x * (1 - cosTheta);
    rotationMatrix.m[0][1] = axis->x * axis->y * (1 - cosTheta) - axis->z * sinTheta;
    rotationMatrix.m[0][2] = axis->x * axis->z * (1 - cosTheta) + axis->y * sinTheta;

    rotationMatrix.m[1][0] = axis->y * axis->x * (1 - cosTheta) + axis->z * sinTheta;
    rotationMatrix.m[1][1] = cosTheta + axis->y * axis->y * (1 - cosTheta);
    rotationMatrix.m[1][2] = axis->y * axis->z * (1 - cosTheta) - axis->x * sinTheta;

    rotationMatrix.m[2][0] = axis->z * axis->x * (1 - cosTheta) - axis->y * sinTheta;
    rotationMatrix.m[2][1] = axis->z * axis->y * (1 - cosTheta) + axis->x * sinTheta;
    rotationMatrix.m[2][2] = cosTheta + axis->z * axis->z * (1 - cosTheta);

    return rotationMatrix;
}

t_vec3 rotatePoint(t_vec3 *point, t_vec3 *center, t_matrix3x3 *rotationMatrix) {
    // Trasladar el sistema de coordenadas al centro de rotación
    point->x -= center->x;
    point->y -= center->y;
    point->z -= center->z;

    // Multiplicar por la matriz de rotación
    t_vec3 rotatedPoint;
    rotatedPoint.x = rotationMatrix->m[0][0] * point->x + rotationMatrix->m[0][1] * point->y + rotationMatrix->m[0][2] * point->z;
    rotatedPoint.y = rotationMatrix->m[1][0] * point->x + rotationMatrix->m[1][1] * point->y + rotationMatrix->m[1][2] * point->z;
    rotatedPoint.z = rotationMatrix->m[2][0] * point->x + rotationMatrix->m[2][1] * point->y + rotationMatrix->m[2][2] * point->z;

    // Volver a la posición original trasladando de nuevo al centro de rotación
    rotatedPoint.x += center->x;
    rotatedPoint.y += center->y;
    rotatedPoint.z += center->z;

    return rotatedPoint;
}

t_color	get_color_cylinder(t_vec3 *p_hit, t_world *objs)
{
	t_uv		uv;
	t_point3	center;
	t_ray		ray;

	if (objs->materia.texture == DEFAULT)
		return (objs->materia.color);
	ray.dir = objs->type.cy->dir;
	ray.orig = objs->type.cy->center;
	center = ray_at(&ray, objs->type.cy->height / 2);
	t_vec3	dir_z = (t_point3){0,0,1};
	double tmp = dot(&objs->type.cy->dir, &dir_z) / (length(&objs->type.cy->dir) * length(&dir_z));
	double theta = acos(tmp);
	t_vec3	tmp_vec = cross(&objs->type.cy->dir, &dir_z);
	t_vec3	rotation_axiz = division_vec3_r(&tmp_vec, length(&tmp_vec));
	rotation_axiz = unit_vector(&rotation_axiz);
	t_matrix3x3 mat_rot = calculateRotationMatrix(theta, &rotation_axiz);
	t_point3 rot_p_hit = rotatePoint(p_hit, &center, &mat_rot);

	uv = get_cylinder_map(&rot_p_hit, &objs->type.cy->center, objs->type.cy->height);
	return (checker_color(uv, objs->materia.color));
}
