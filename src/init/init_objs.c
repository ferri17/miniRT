/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/12 19:40:43 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_world	*push_back(t_world *objs, t_scene *scene)
{
	if (objs)
	{
		while (objs->next)
			objs = objs->next;
		objs->next = malloc(sizeof(t_world));
		objs = objs->next;
	}
	else
	{
		scene->objs = malloc(sizeof(t_world));
		objs = scene->objs;
	}
	return (objs);
}


int	check_sphere(t_scene *scene, char **split)
{
	t_world	*sp;

	sp = push_back(scene->objs, scene);
	if (!sp)
		return (1);
	sp->next = NULL;
	sp->type.sp = malloc(sizeof(t_sphere));
	sp->free_type = free_sphere;
	if (fill_sphere(sp->type.sp, split) || put_colors(&sp->materia.color, split[3]))
		return (1);
	if (ft_array_len(split) == 5)
	{
		if (ft_strcmp(split[4], "CHECKBOARD") == 0)
			sp->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		sp->materia.texture = DEFAULT;
	sp->get_color = get_color_sphere; 
	sp->hit = hit_sphere;
	sp->get_position_pointer = get_position_sphere;
	return (0);
}

int	check_plane(t_scene *scene, char **split)
{
	t_world	*pl;

	pl = push_back(scene->objs, scene);
	if (!pl)
		return (1);
	pl->next = NULL;
	pl->type.pl = malloc(sizeof(t_plane));
	pl->free_type = free_plane;
	if (fill_plane(pl->type.pl, split) || put_colors(&pl->materia.color, split[3]))
		return (1);
	if (ft_array_len(split) == 5)
	{
		if (ft_strcmp(split[4], "CHECKBOARD") == 0)
			pl->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	pl->get_color = get_color_plane;
	pl->hit = hit_plane;
	pl->get_position_pointer = get_position_plane;
	return (0);
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

int	check_cylinder(t_scene *scene, char **split)
{
	t_world	*cy;
	t_ray	ray;

	cy = push_back(scene->objs, scene);
	if (!cy)
		return (1);
	cy->next = NULL;
	cy->type.cy = malloc(sizeof(t_cylinder));
	cy->free_type = free_cylinder;
	if (fill_cylinder(cy->type.cy, split) || put_colors(&cy->materia.color, split[5]))
		return (1);
	if (ft_array_len(split) == 7)
	{
		if (ft_strcmp(split[6], "CHECKBOARD") == 0)
			cy->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		cy->materia.texture = DEFAULT;
	cy->type.cy->dir = unit_vector(&cy->type.cy->dir);
	ray.dir = cy->type.cy->dir;
	ray.orig = cy->type.cy->center;
	printf("old dir(%f, %f, %f)\n", ray.dir.x, ray.dir.y, ray.dir.z);
	t_vec3	new_dir = {0,1,0};
	double	angle;
	angle = acos(dot(&new_dir, &ray.dir) / (length(&new_dir) * length(&ray.dir)));
	t_vec3	cosa = cross(&ray.dir, &new_dir);

	cy->type.cy->dir = rotarVector(ray.dir, cosa, angle);
	ray.dir = cy->type.cy->dir;
	printf("new dir(%f, %f, %f)\n", ray.dir.x, ray.dir.y, ray.dir.z);
	cy->type.cy->center = ray_at(&ray, -(cy->type.cy->height / 2));
	cy->hit = hit_cylinder;
	cy->get_position_pointer = get_position_cylinder;
	cy->get_color = get_color_cylinder;
	return (0);
}

int	check_cone(t_scene *scene, char **split)
{
	t_world	*cn;

	cn = push_back(scene->objs, scene);
	if (!cn)
		return (1);
	cn->next = NULL;
	cn->type.cn = malloc(sizeof(t_cone));
	cn->free_type = free_cone;
	if (fill_cone(cn->type.cn, split) || put_colors(&cn->materia.color, split[5]))
		return (1);
	if (ft_array_len(split) == 7)
	{
		if (ft_strcmp(split[6], "CHECKBOARD") == 0)
			cn->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		cn->materia.texture = DEFAULT;
	cn->type.cn->angle = deg_to_rad(cn->type.cn->angle);
	cn->type.cn->dir = unit_vector(&cn->type.cn->dir);
	cn->hit = hit_disk_cone;
	cn->get_position_pointer = get_position_cone;
	cn->get_color = get_color_cone;
	return (0);
}
