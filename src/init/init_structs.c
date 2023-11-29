/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:18:57 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/29 20:05:00 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	init_structs(t_scene *scene)
{
	scene->ambligth.init = false;
	scene->camera.init = false;
	scene->objs = NULL;
	scene->data.img.ptr = NULL;
}
