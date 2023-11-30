/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/30 20:03:47 by fbosch           ###   ########.fr       */
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
	return (true);
}

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
	return (0);
}

bool	hit_cylinder(const t_ray *ray, t_objects obj, t_hit *hit_record)
{
	t_cylinder	*cy;

	(void)hit_record;
	(void)ray;
	cy = obj.cy;
	//printf("Cylinder: Color: r: %f g: %f b: %f\n", cy->color.e[R], cy->color.e[G], cy->color.e[B]);
	return (false);
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
	cy->hit = hit_cylinder;
	return (0);
}
