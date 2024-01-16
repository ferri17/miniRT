/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:12:11 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/16 15:37:28 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

void	put_texture_sphere(t_objects *type, t_point3 *p_hit)
{
	t_uv	uv;
	int		width;
	int		height;
	void	*img_ptr;
	int		bits;
	int		size;
	int		endian;
	char	*data;
	char	*color;
	static	int test = 0;

	uv = get_spherical_map(p_hit, &type->sp->center, type->sp->radius);
	img_ptr = mlx_xpm_file_to_image(mlx_init(), "playerB.xpm", &width, &height);
	data = mlx_get_data_addr(img_ptr, &bits, &size, &endian);
	double	w = uv.u * width;
	double	h = uv.v * height;
	color = data + ((int)(w * size) + (int)(h * (bits / 8)));
	if(test == 0)
	{
		ft_printf("%d\n", *color);
		test++;
	}
}
