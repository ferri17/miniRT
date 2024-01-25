/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:39:49 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/25 20:04:23 by apriego-         ###   ########.fr       */
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

int	check_img(t_img_tex *img, void *mlx_ptr, char *name)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, name, &img->w, &img->h);
	if (img->img_ptr == NULL)
		return (1);
	img->info = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->sl, &img->endian);
	if (img->info == NULL)
		return (1);
	return (0);
}

int	bitmap_bumpmap_case(t_scene *scene, t_world *sp, char **split, int pos)
{
	t_materia	*m;

	m = &sp->materia;
	if (ft_strcmp(split[pos], "BITMAP_BUMPMAP") == 0)
		sp->materia.texture = BITMAP_BUMPMAP;
	else
		return (1);
	if (check_img(&m->bump, scene->data.mlx, split[pos + 1]))
		return (1);
	if (check_img(&m->bit, scene->data.mlx, split[pos + 2]))
		return (1);
	return (0);
}

int	bitmap_or_bumpmap_case(t_scene *sc, t_world *sp, char **s, int pos)
{
	t_materia	*m;

	m = &sp->materia;
	if (ft_strcmp(s[pos], "BITMAP") == 0)
		m->texture = BITMAP;
	else if (ft_strcmp(s[pos], "BUMPMAP") == 0)
		m->texture = BUMPMAP;
	else
		return (1);
	if (m->texture == BUMPMAP)
		return (check_img(&m->bump, sc->data.mlx, s[pos + 1]));
	else
		return (check_img(&m->bit, sc->data.mlx, s[pos + 1]));
	return (0);
}

int	check_texture_sphere(t_scene *scene, t_world *sp,char **split)
{
	if (ft_array_len(split) == 7)
		sp->materia.texture = DEFAULT;
	else if (ft_array_len(split) == 8)
	{
		if (ft_strcmp(split[7], "CHECKBOARD") == 0)
			sp->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else if (ft_array_len(split) == 9)
		return (bitmap_or_bumpmap_case(scene, sp, split, 7));
	else if (ft_array_len(split) == 10)
		return (bitmap_bumpmap_case(scene, sp, split, 7));
	return (0);
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
	if (fill_sphere(sp->type.sp, split) || check_materia(sp, split, 3)
		|| put_colors(&sp->materia.color, split[6]))
		return (1);
	if (check_texture_sphere(scene, sp, split))
		return (1);
	sp->get_color = get_color_sphere;
	sp->hit = hit_sphere;
	sp->get_position_pointer = get_position_sphere;
	sp->get_normal_map = get_normal_map_sphere;
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
	if (fill_plane(pl->type.pl, split) || check_materia(pl, split, 3)
		|| put_colors(&pl->materia.color, split[6]))
		return (1);
	if (check_dir(&pl->type.pl->normal))
		return (1);
	if (ft_array_len(split) == 8)
	{
		if (ft_strcmp(split[7], "CHECKBOARD") == 0)
			pl->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		pl->materia.texture = DEFAULT;
	pl->type.pl->normal = unit_vector(&pl->type.pl->normal);
	pl->get_color = get_color_plane;
	pl->hit = hit_plane;
	pl->get_position_pointer = get_position_plane;
	return (0);
}

int	check_cylinder(t_scene *scene, char **split)
{
	t_world	*cy;

	cy = push_back(scene->objs, scene);
	if (!cy)
		return (1);
	cy->next = NULL;
	cy->type.cy = malloc(sizeof(t_cylinder));
	cy->free_type = free_cylinder;
	if (fill_cylinder(cy->type.cy, split) || check_materia(cy, split, 5)
		|| put_colors(&cy->materia.color, split[8]))
		return (1);
	if (check_dir(&cy->type.cy->dir))
		return (1);
	if (ft_array_len(split) == 10)
	{
		if (ft_strcmp(split[9], "CHECKBOARD") == 0)
			cy->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		cy->materia.texture = DEFAULT;
	inti_func_cylinder(cy);
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
	if (fill_cone(cn->type.cn, split) || check_materia(cn, split, 5)
		|| put_colors(&cn->materia.color, split[8]))
		return (1);
	if (check_dir(&cn->type.cn->dir))
		return (1);
	if (ft_array_len(split) == 10)
	{
		if (ft_strcmp(split[9], "CHECKBOARD") == 0)
			cn->materia.texture = CHECKBOARD;
		else
			return (1);
	}
	else
		cn->materia.texture = DEFAULT;
	inti_func_cone(cn);
	return (0);
}
