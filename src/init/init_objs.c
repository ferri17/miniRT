/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/05 15:35:12 by apriego-         ###   ########.fr       */
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

	sqrtd = sqrt(discriminant);
	if (discriminant < 0)
        return (false);
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

/* 
	vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0)
        return -1.0;
    else
    	return (-half_b - sqrt(discriminant) ) / a;
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
	sp->type.sp = malloc(sizeof(t_sphere)); //PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	if (fill_sphere(sp->type.sp, split) || put_colors(&sp->color, split[3]))
		return (1);
	sp->hit = hit_sphere;
	sp->free_type = free_sphere;
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
		return false;
	d = dot(&pl->normal, &pl->center);
	t = (d - dot(&pl->normal, &ray->orig)) / denom;
		if (t <= rec->ray_tmin || t >= rec->ray_tmax)
			return (false);
        rec->t = t;
        rec->p = ray_at(ray, t);
        rec->normal = pl->normal;

        return true;
}

/* double divisor = dot(normal, r.direction());
if (fabs(divisor) < 1e-6)
	return false;
double solution = (dot(normal, center) - dot(normal, r.origin())) / divisor;
if (!ray_t.surrounds(solution))
	return false;
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
	pl->type.pl = malloc (sizeof(t_plane)); //PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	if (fill_plane(pl->type.pl, split) || put_colors(&pl->color, split[3]))
		return (1);
	pl->hit = hit_plane;
	pl->free_type = free_plane;
	return (0);
}

t_vec3 calculate_normal(const t_cylinder *cylinder, const t_point3 p) {
    t_vec3 tmp = {p.e[0] - cylinder->center.e[0], p.e[1] - cylinder->center.e[1], p.e[2] - cylinder->center.e[2]};
    t_vec3 tmp2 = {
        tmp.e[0] - cylinder->dir.e[0] * dot(&tmp, &cylinder->dir),
        tmp.e[1] - cylinder->dir.e[1] * dot(&tmp, &cylinder->dir),
        tmp.e[2] - cylinder->dir.e[2] * dot(&tmp, &cylinder->dir)
    };
    return unit_vector(&tmp2);
}

bool	hit_cylinder(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_cylinder	*cy;

	cy = obj.cy;

    t_vec3 oc = substract_vec3(&ray->orig, &cy->center);

    // Proyecta el vector de dirección del rayo en el plano del cilindro
	t_vec3 tmp = product_vec3_r(&cy->dir, dot(&ray->dir, &cy->dir));
    t_vec3 direction_parallel = substract_vec3(&ray->dir, &tmp);

    // Proyecta el vector desde el origen al centro del cilindro en el plano del cilindro
	tmp = product_vec3_r(&cy->dir, dot(&oc, &cy->dir));
    t_vec3 oc_parallel = substract_vec3(&oc, &tmp);

    double a = length_squared(&direction_parallel);
    double half_b = dot(&oc_parallel, &direction_parallel);
    double c = length_squared(&oc_parallel) - cy->radius * cy->radius;

    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;
    if (root <= rec->ray_tmin || root >= rec->ray_tmax) {
        root = (-half_b + sqrtd) / a;
        if (root <= rec->ray_tmin || root >= rec->ray_tmax)
            return false;
    }

    rec->t = root;
    rec->p = ray_at(ray, root);

    // Verifica que la intersección esté dentro de la altura del cilindro
    tmp = substract_vec3(&rec->p, &cy->center);
    double projection = dot(&cy->dir, &tmp);

	if (projection < 0 || projection > cy->height) {
		// La intersección está fuera de la altura del cilindro
		return false;
	}

	rec->normal = calculate_normal(cy, rec->p);
    return true;
}

t_vec3 translate_point_in_direction(const t_vec3 *point, double distance, const t_vec3 *direction) {
    t_vec3 result;
    result.e[0] = point->e[0] + distance * direction->e[0];
    result.e[1] = point->e[1] + distance * direction->e[1];
    result.e[2] = point->e[2] + distance * direction->e[2];
    return result;
}

bool hit_disk(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_cylinder *disk;

	disk = obj.cy;
	disk->dir = unit_vector(&disk->dir);
    double denom = dot(&disk->dir, &ray->dir);
    
    if (fabs(denom) < 1e-8) {
        return false;
    }

    t_vec3 oc = substract_vec3(&disk->center, &ray->orig);
    double t = dot(&oc, &disk->dir) / denom;

    if (t <= rec->ray_tmin || t >= rec->ray_tmax) {
        return false;
    }

    t_vec3 p = ray_at(ray, t);

    t_vec3 to_center = substract_vec3(&p, &disk->center);
    double distance_squared = dot(&to_center, &to_center);

    if (distance_squared > disk->radius * disk->radius) {
        return false;
    }

    rec->t = t;
    rec->p = p;
    rec->normal = disk->dir;

    return true;
}

bool hit_2disk(const t_ray *ray, t_objects obj, t_hit *rec)
{
	bool r[3];
	t_objects tmp;

	tmp.cy = malloc(sizeof(t_cylinder));
	tmp.cy->center = translate_point_in_direction(&obj.cy->center, 2, &obj.cy->dir);
	tmp.cy->dir = obj.cy->dir;
	tmp.cy->height = obj.cy->height;
	tmp.cy->radius = obj.cy->radius;
	r[0] = hit_disk(ray, obj, rec);
	r[1] = hit_disk(ray, tmp, rec);
	r[2] = hit_cylinder(ray, obj, rec);
	free(tmp.cy);
	return (r[0] || r[1] || r[2]);
}

int	check_cylinder(t_scene *scene, char **split)
{
	t_world	*cy;

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
	cy->type.cy = malloc(sizeof(t_cylinder)); //PROTEEEEEEEEEEEEEEEEEEEEEEEEEEECT MALLOC?
	if (fill_cylinder(cy->type.cy, split) || put_colors(&cy->color, split[5]))
		return (1);
	cy->hit = hit_2disk;
	cy->free_type = free_cylinder;
	return (0);
}
