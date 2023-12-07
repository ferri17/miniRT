/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/07 15:39:05 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

// SEND OBJ BY ADDRESS
bool	hit_sphere(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_sphere	*sp;
	t_vec3		oc;
	t_evars		vars;

	sp = obj.sp;
	oc = substract_vec3(&ray->orig, &sp->center);
	vars.a = length_squared(&ray->dir);
	vars.half_b = dot(&oc, &ray->dir);
	vars.c = length_squared(&oc) - (sp->radius * sp->radius);
	vars.discriminant = (vars.half_b * vars.half_b) - (vars.a * vars.c);
	vars.sqrtd = sqrt(vars.discriminant);
	if (vars.discriminant < 0)
		return (false);
	vars.root = (-vars.half_b - vars.sqrtd) / vars.a;
	if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
	{
		vars.root = (-vars.half_b + vars.sqrtd) / vars.a;
		if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
			return (false);
	}
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	rec->normal = substract_vec3(&rec->p, &sp->center);
	division_vec3(&rec->normal, sp->radius);
	return (true);
}

/*
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius*radius;
	auto discriminant = half_b*half_b - a*c;

	if (discriminant < 0)
		return (-1.0);
	else
		return ((-half_b - sqrt(discriminant) ) / a);
*/

int	check_sphere(t_scene *scene, char **split)
{
	t_world	*sp;

	sp = scene->objs;
	if (sp)
	{
		while (sp->next)
			sp = sp->next;
		sp->next = malloc(sizeof(t_world));
		sp = sp->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		sp = scene->objs;
	}
	if (!sp)
		return (1);
	sp->next = NULL;
	sp->type.sp = malloc(sizeof(t_sphere));
		// PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	sp->free_type = free_sphere;
	if (fill_sphere(sp->type.sp, split) || put_colors(&sp->color, split[3]))
		return (1);
	sp->hit = hit_sphere;
	return (0);
}

bool	hit_plane(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_plane	*pl;
	double	denom;
	double	t;
	double	d;

	pl = obj.pl;
	denom = dot(&pl->normal, &ray->dir);
	if (fabs(denom) < 1e-8)
		return (false);
	d = dot(&pl->normal, &pl->center);
	t = (d - dot(&pl->normal, &ray->orig)) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = pl->normal;
	return (true);
}

/* double divisor = dot(normal, r.direction());
if	(fabs(divisor) < 1e-6)
	return (false);
double	solution = (dot(normal, center) - dot(normal, r.origin())) / divisor;
if (!ray_t.surrounds(solution))
	return (false);
rec.t = solution;
rec.p = r.at(rec.t);
rec.normal = normal;
rec.mat = mat;
return (rec.t >= 0); */

int	check_plane(t_scene *scene, char **split)
{
	t_world	*pl;

	pl = scene->objs;
	if (pl)
	{
		while (pl->next)
			pl = pl->next;
		pl->next = malloc(sizeof(t_world));
		pl = pl->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		pl = scene->objs;
	}
	if (!pl)
		return (1);
	pl->next = NULL;
	pl->type.pl = malloc(sizeof(t_plane));
		// PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	pl->free_type = free_plane;
	if (fill_plane(pl->type.pl, split) || put_colors(&pl->color, split[3]))
		return (1);
	pl->hit = hit_plane;
	return (0);
}

t_vec3	calculate_normal(const t_cylinder *cylinder, const t_point3 p)
{
    t_vec3 tmp;
    t_vec3 tmp2;
	t_vec3 normal;

	tmp = substract_vec3(&cylinder->center, &p);
	tmp2 = product_vec3_r(&cylinder->dir, dot(&tmp, &cylinder->dir));
	normal = substract_vec3(&tmp2, &tmp);
	return (unit_vector(&normal));
}

bool	calc_hit_cilinder(t_evars vars, const t_ray *ray, t_hit *rec, t_objects obj)
{
	double	projection;
	t_vec3 tmp;

	if (vars.discriminant < 0)
		return (false);
	vars.sqrtd = sqrt(vars.discriminant);
	vars.root = (-vars.half_b - vars.sqrtd) / vars.a;
	if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
	{
		vars.root = (-vars.half_b + vars.sqrtd) / vars.a;
		if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
			return (false);
	}
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	tmp = substract_vec3(&rec->p, &obj.cy->center);
	projection = dot(&obj.cy->dir, &tmp);
	if (projection < 0 || projection > obj.cy->height)
		return (false);
	rec->normal = calculate_normal(obj.cy, rec->p);
	return (true);
}

bool	hit_cylinder(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_vec3	oc;
	t_vec3	tmp;
	t_vec3	direction_parallel;
	t_vec3	oc_parallel;
	t_evars	vars;

	oc = substract_vec3(&ray->orig, &obj.cy->center);
	tmp = product_vec3_r(&obj.cy->dir, dot(&ray->dir, &obj.cy->dir));
	direction_parallel = substract_vec3(&ray->dir, &tmp);
	tmp = product_vec3_r(&obj.cy->dir, dot(&oc, &obj.cy->dir));
	oc_parallel = substract_vec3(&oc, &tmp);
	vars.a = length_squared(&direction_parallel);
	vars.half_b = dot(&oc_parallel, &direction_parallel);
	vars.c = length_squared(&oc_parallel) - obj.cy->radius * obj.cy->radius;
	vars.discriminant = vars.half_b * vars.half_b - vars.a * vars.c;
	return (calc_hit_cilinder(vars, ray, rec, obj));
}

bool	hit_disk(const t_ray *ray, t_objects obj, t_hit *rec)
{
	double	denom;
	t_vec3	oc;
	double	t;
	t_vec3	p;
	t_vec3	to_center;

	denom = dot(&obj.cy->dir, &ray->dir);
	if (fabs(denom) < 1e-8)
		return (false);
	oc = substract_vec3(&obj.cy->center, &ray->orig);
	t = dot(&oc, &obj.cy->dir) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	p = ray_at(ray, t);
	to_center = substract_vec3(&p, &obj.cy->center);
	if (dot(&to_center, &to_center) > obj.cy->radius * obj.cy->radius)
		return (false);
	rec->t = t;
	rec->p = p;
	rec->normal = product_vec3_r(&obj.cy->dir, -1);
	return (true);
}

bool	hit_2disk(const t_ray *ray, t_objects obj, t_hit *rec)
{
	bool		r[3];
	t_objects	tmp;
	t_ray		displace;

	tmp.cy = malloc(sizeof(t_cylinder));
	obj.cy->dir = unit_vector(&obj.cy->dir);
	displace.orig = obj.cy->center;
	displace.dir = obj.cy->dir;
	tmp.cy->center = obj.cy->center;
	tmp.cy->dir = obj.cy->dir;
	tmp.cy->height = obj.cy->height;
	tmp.cy->radius = obj.cy->radius;
	r[0] = hit_disk(ray, tmp, rec);
	tmp.cy->center = ray_at(&displace, obj.cy->height);
	tmp.cy->dir = product_vec3_r(&obj.cy->dir, -1);
	r[1] = hit_disk(ray, tmp, rec);
	r[2] = hit_cylinder(ray, obj, rec);
	free(tmp.cy);
	return (r[0] || r[1] || r[2]);
}

int	check_cylinder(t_scene *scene, char **split)
{
	t_world	*cy;
	t_ray	ray;

	cy = scene->objs;
	if (cy)
	{
		while (cy->next)
			cy = cy->next;
		cy->next = malloc(sizeof(t_world));
		cy = cy->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		cy = scene->objs;
	}
	if (!cy)
		return (1);
	cy->next = NULL;
	cy->type.cy = malloc(sizeof(t_cylinder));
		// PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	cy->free_type = free_cylinder;
	if (fill_cylinder(cy->type.cy, split) || put_colors(&cy->color, split[5]))
		return (1);
	ray.dir = cy->type.cy->dir;
	ray.orig = cy->type.cy->center;
	cy->type.cy->center = ray_at(&ray, -(cy->type.cy->height / 2));
	cy->hit = hit_2disk;
	return (0);
}

int	check_cone(t_scene *scene, char **split)
{
	t_world *cn;

	cn = scene->objs;
	if (cn)
	{
		while (cn->next)
			cn = cn->next;
		cn->next = malloc(sizeof(t_world));
		cn = cn->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		cn = scene->objs;
	}
	if (!cn)
		return (1);
	cn->next = NULL;
	cn->type.cn = malloc(sizeof(t_cone));
		// PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	cn->free_type = free_cone;
	if (fill_cone(cn->type.cn, split) || put_colors(&cn->color, split[5]))
		return (1);
	cn->type.cn->angle = degree_to_radians(cn->type.cn->angle);
	cn->hit = hit_cone;
	return (0);
}