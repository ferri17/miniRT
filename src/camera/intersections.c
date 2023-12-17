/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:39:44 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/16 02:11:10 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

//SEND OBJ BY ADDRESS
bool	hit_sphere(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_sphere	*sp;
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		root;
	double		sqrtd;

	sp = obj.sp;
	oc = substract_vec3(&ray->orig, &sp->center);
	a = length_squared(&ray->dir);
	half_b = dot(&oc, &ray->dir);
	c = length_squared(&oc) - (sp->radius * sp->radius);
	discriminant = (half_b * half_b) - (a * c);
	if (discriminant < 0)
        return (false);
	sqrtd = sqrt(discriminant);
    root = (-half_b - sqrtd) / a;
	if (root <= rec->ray_tmin || root >= rec->ray_tmax)
	{
    	root = (-half_b + sqrtd) / a;
		if (root <= rec->ray_tmin || root >= rec->ray_tmax)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = substract_vec3(&rec->p, &sp->center);
	division_vec3(&rec->normal, sp->radius);
    return (true);
}

bool	hit_plane(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_plane	*pl;
	double	denom;
	double	t;
	double	d;
	
	pl = obj.pl;
	denom = dot(&pl->normal, &ray->dir);
	if (fabs(denom) < BIAS)
		return false;
	d = dot(&pl->normal, &pl->center);
	t = (d - dot(&pl->normal, &ray->orig)) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = pl->normal;
	return (true);
}

bool	hit_cylinder(const t_ray *ray, t_objects obj, t_hit *hit_record)
{
	t_cylinder	*cy;

	(void)cy;
	(void)hit_record;
	(void)ray;
	cy = obj.cy;
	//printf("Cylinder: Color: r: %f g: %f b: %f\n", cy->color.e[R], cy->color.e[G], cy->color.e[B]);
	return (false);
}
