/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:59:36 by apriego-          #+#    #+#             */
/*   Updated: 2024/02/01 17:57:25 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	check_img(t_img_tex **img, void *mlx_ptr, char *name)
{
	*img = malloc(sizeof(t_img_tex));
	if (!(*img))
		return (1);
	(*img)->img_ptr = mlx_xpm_file_to_image(mlx_ptr, name, &(*img)->w,
			&(*img)->h);
	if ((*img)->img_ptr == NULL)
		return (1);
	(*img)->info = mlx_get_data_addr((*img)->img_ptr, &(*img)->bpp, &(*img)->sl,
			&(*img)->end);
	if ((*img)->info == NULL)
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
	if (check_img(&m->bit, scene->data.mlx, split[pos + 1]))
		return (1);
	if (check_img(&m->bump, scene->data.mlx, split[pos + 2]))
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
