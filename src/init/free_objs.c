/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:23:45 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/12 13:12:23 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	free_plane(t_objects obj)
{
	t_plane	*pl;

	pl = obj.pl;
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
	free(cy);
}

void	free_cone(t_objects obj)
{
	t_cone	*cn;

	cn = obj.cn;
	free(cn);
}
