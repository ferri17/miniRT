/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:18:57 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/08 18:39:32 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_scene	init_structs(void)
{
	t_scene	scene;

	scene.objs.cy = NULL;
	scene.objs.pl = NULL;
	scene.objs.sp = NULL;
	return (scene);
}
