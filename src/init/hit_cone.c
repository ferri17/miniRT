/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:00:29 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/06 18:42:01 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3 calculate_normal_cone(const t_cone *cone, const t_vec3 *p, double projection)
{
    t_vec3 normal;
    t_vec3 tmp = substract_vec3(p, &cone->apex);

    double radius_at_point = projection * tan(cone->angle);

    // Calcula la normal en el punto proyectado
    t_vec3 tmp1 = product_vec3_r(&cone->dir, projection);

    normal = substract_vec3(&tmp, &tmp1);
    normal = unit_vector(&normal);

    // Ajusta la normal para tener en cuenta el radio del cono
	tmp1 = product_vec3_r(&cone->dir, radius_at_point);
    normal = add_vec3(&normal, &tmp1);

    return (unit_vector(&normal));
}


// Función para calcular el cuadrado de un número
bool calc_hit_cone(t_evars vars, const t_ray *ray, t_hit *rec, t_objects obj)
{
    double projection;

    if (vars.discriminant < 0)
        return false;

    vars.sqrtd = sqrt(vars.discriminant);
    vars.root = (-vars.half_b - vars.sqrtd) / vars.a;

    if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
    {
        vars.root = (-vars.half_b + vars.sqrtd) / vars.a;

        if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
            return false;
    }

    rec->t = vars.root;
    rec->p = ray_at(ray, vars.root);

    t_vec3 tmp = substract_vec3(&rec->p, &obj.cn->apex);
    projection = dot(&tmp, &obj.cn->dir);

    if (projection < 0 || projection > obj.cn->height)
        return false;

    rec->normal = calculate_normal_cone(obj.cn, &rec->p, projection);
    return true;
}

bool hit_cone(const t_ray *ray, t_objects obj, t_hit *rec)
{
    t_vec3 oc = substract_vec3(&ray->orig, &obj.cn->apex);
    t_vec3 tmp = product_vec3_r(&obj.cn->dir, dot(&ray->dir, &obj.cn->dir));
    t_vec3 direction_parallel = substract_vec3(&ray->dir, &tmp);
    tmp = product_vec3_r(&obj.cn->dir, dot(&oc, &obj.cn->dir));
    t_vec3 oc_parallel = substract_vec3(&oc, &tmp);

    t_evars vars;
    vars.a = length_squared(&direction_parallel) - pow(tan(obj.cn->angle), 2);
    vars.half_b = dot(&oc_parallel, &direction_parallel) - dot(&oc, &obj.cn->dir) * dot(&ray->dir, &obj.cn->dir) * tan(obj.cn->angle);
    vars.c = length_squared(&oc_parallel) - pow(dot(&oc, &obj.cn->dir), 2);
    vars.discriminant = vars.half_b * vars.half_b - vars.a * vars.c;

    return calc_hit_cone(vars, ray, rec, obj);
}
