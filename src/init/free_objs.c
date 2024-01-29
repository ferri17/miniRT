/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:23:45 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/28 11:36:59 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	free_plane(t_objects obj)
{
	t_plane	*pl;

	pl = obj.pl;
	if (pl)
		free(pl);
}

void	free_sphere(t_objects obj)
{
	t_sphere	*sp;

	sp = obj.sp;
	if (sp)
		free(sp);
}

void	free_cylinder(t_objects obj)
{
	t_cylinder	*cy;

	cy = obj.cy;
	if (cy)
		free(cy);
}

void	free_cone(t_objects obj)
{
	t_cone	*cn;

	cn = obj.cn;
	if (cn)
		free(cn);
}
