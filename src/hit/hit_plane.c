/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:59:49 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/14 12:58:25 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

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
	if (t < rec->ray_tmin || t > rec->ray_tmax)
		return (false);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = pl->normal;
	return (true);
}
