/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:00:29 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/07 15:43:59 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

bool intersect_ray_cone(const t_ray ray, const t_cone *cone, t_vec3 intersection_point) {
    // Calcular los coeficientes de la ecuación cuadrática

    double a =  pow(dot(&ray.dir, &cone->dir), 2) - pow(cos(cone->angle), 2);
    t_vec3 tmp = substract_vec3(&ray.orig, &cone->apex);
    double b = 2 * (dot(&ray.dir, &cone->dir) * dot(&tmp, &cone->dir) - dot(&ray.dir, &tmp) * pow(cos(cone->angle), 2));
    double c = pow(dot(&tmp, &cone->dir), 2) - dot(&tmp, &tmp) * pow(cos(cone->angle), 2);

    // Resolver la ecuación cuadrática
    double discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0) {
        // No hay intersección real
        return false;
    } else {
        // Encontrar el punto de intersección más cercano
        double t = (-b - sqrt(discriminant)) / (2 * a);
        if (t < 0) {
            t = (-b + sqrt(discriminant)) / (2 * a);
        }
        tmp = add_vec3(&ray.orig, &ray.dir);
        intersection_point = product_vec3_r(&tmp, t);
        return true;
    }
}

t_vec3 normal_at_intersection(const t_vec3 intersection_point, const t_cone *cone) {
    // Calcular la dirección del vector normal
    t_vec3 tmp = substract_vec3(&intersection_point, &cone->apex);
    t_vec3 normal_direction = unit_vector(&tmp);

    // Proyectar la dirección del vector normal sobre la dirección del eje del cono
    double projection = dot(&cone->dir, &normal_direction);
    tmp = product_vec3_r(&cone->dir, projection);
    t_vec3 normal = substract_vec3(&normal_direction, &tmp);
    double test = length(&normal);
    if (test == 0) {
        // El punto de intersección está en el eje del cono
        normal = cone->dir;
    } else {
        // Normalizar el vector resultante
        normal = unit_vector(&normal);
    }

    return normal;
}

bool hit_cone(const t_ray *ray, t_objects obj, t_hit *rec) {

    // Encontrar la intersección entre el rayo y el cono
    t_vec3 intersection_point = {0, 0, 0};
    obj.cn->dir = unit_vector(&obj.cn->dir);
    obj.cn->apex = unit_vector(&obj.cn->apex);
    if (!intersect_ray_cone(*ray, obj.cn, intersection_point)) {
        return false;
    }

    // Calcular la normal en el punto de intersección
    t_vec3 normal = normal_at_intersection(intersection_point, obj.cn);

    // Guardar los datos de la intersección en la estructura t_hit
    t_vec3 tmp = substract_vec3(&intersection_point, &ray->orig);
    rec->t = length(&tmp);
    rec->p = intersection_point;
    rec->normal = normal;
    return true;
}
