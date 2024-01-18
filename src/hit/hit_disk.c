/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:56 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/16 02:11:10 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MiniRT.h>

bool	hit_disk(const t_ray *ray, t_disk *disk, t_hit *rec)
{
	double	denom;
	t_vec3	oc;
	double	t;
	t_vec3	p;
	t_vec3	to_center;

	denom = dot(&disk->dir, &ray->dir);
	if (fabs(denom) < BIAS)
		return (false);
	oc = substract_vec3(&disk->center, &ray->orig);
	t = dot(&oc, &disk->dir) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	p = ray_at(ray, t);
	to_center = substract_vec3(&p, &disk->center);
	if (dot(&to_center, &to_center) > disk->radius * disk->radius)
		return (false);
	rec->t = t;
	rec->p = p;
	rec->normal = product_vec3_r(&disk->dir, -1);
	return (true);
}
