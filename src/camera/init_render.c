/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:38:42 by fbosch            #+#    #+#             */
/*   Updated: 2023/12/06 16:07:34 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	send_ray(const t_ray *r, t_scene *scene)
{
	t_color	hit;
	t_hit	tmp_hit;
	t_world	*objs;
	bool	any_hit = false;
	
	tmp_hit.ray_tmin = 0;
	tmp_hit.ray_tmax = INT_MAX;
	objs = scene->objs;
	while (objs)
	{
		if (objs->hit(r, objs->type, &tmp_hit))
		{
			tmp_hit.ray_tmax = tmp_hit.t;
			tmp_hit.normal = product_vec3_r(&tmp_hit.normal, -1);
			t_vec3 unit = unit_vector(&tmp_hit.normal);
			//t_vec3 unit = unit_vector(&objs->color);
			t_color color = {unit.x+1, unit.y+1, unit.z+1};
			division_vec3(&color, 2);
			hit = color;
			any_hit = true;
		}
		objs = objs->next;
	}
	if (any_hit)
		return (hit);
	/* BACKGROUND */
	t_vec3	unit_direction = unit_vector(&r->dir);
	double	a = 0.5 * (unit_direction.y + 1.0);
	t_color	color1 = {1.0, 1.0, 1.0};
	product_vec3(&color1, (1.0 - a));
	t_color	color2 = {0.5, 0.7, 1.0};
	product_vec3(&color2, a);
	return (add_vec3(&color1, &color2));
	/* BACKGROUND */
}

#include <time.h>

void	render_image(t_scene *scene, int img_w, int img_h)
{
	t_mlx	*data;
	void	*tmp_img_ptr;
	clock_t	t;

	t = clock();
	data = &scene->data;
	tmp_img_ptr = data->img.ptr;
	init_mlx_image(data, img_w, img_h);
	set_camera(&scene->camera, img_w, img_h);
	start_raytracer(data, scene, img_w, img_h);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	if (tmp_img_ptr != NULL)
		mlx_destroy_image(data->mlx, tmp_img_ptr);
	t = clock() - t;
	ft_printf("\r Render time: %ims", (int)((double)t / CLOCKS_PER_SEC * 1000));
}

void	start_raytracer(t_mlx *data, t_scene *scene, int img_w, int img_h)
{
	t_camera	*camera;
	int	i;
	int	j;
	
	camera = &scene->camera;
	j = 0;
	while (j < img_h)
	{
		//ft_printf("\r Scaning line %i/%i", j + 1, WIN_H);
		i = 0;
		while (i < img_w)
		{
			//auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			t_vec3		tmp_i = product_vec3_r(&camera->pixel_delta_u, i);
			t_vec3		tmp_j = product_vec3_r(&camera->pixel_delta_v, j);
			t_point3	pixel_center = add_vec3(&camera->pixel00_loc, &tmp_i);
			pixel_center = add_vec3(&pixel_center, &tmp_j);

            //auto ray_direction = pixel_center - camera_center;
			t_vec3	ray_direction = substract_vec3(&pixel_center, &camera->center);

            //ray r(camera_center, ray_direction);
			t_ray	r;
			r.orig = camera->center;
			r.dir = ray_direction;
	
            t_color pixl = send_ray(&r, scene);
			int	red = pixl.x * 255.999;
			int	green = pixl.y * 255.999;
			int	blue = pixl.z * 255.999;
			int	color = create_color(0, red, green, blue);

			my_put_pixel(data, i, j, color);
			i++;
		}
		j++;
	}
}

void	set_camera(t_camera *camera, int img_w, int img_h)
{
	double	theta;
	double	h;
	t_vec3	vup = {0,1,0}; 
	// Camera
	camera->focal_length = 1.0;
	theta = degree_to_radians(camera->hfov);
	h = tan(theta / 2);
	camera->viewport_width = 2 * h * camera->focal_length;
	camera->viewport_height = camera->viewport_width * ((double)img_h/(double)img_w);

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	//t_vec3	tmp32 = substract_vec3(&camera->center, &camera->dir);
	t_vec3 w = unit_vector(&camera->dir);
    product_vec3(&w, -1);
	t_vec3	tmp9 = cross(&vup, &w);
    t_vec3 u = unit_vector(&tmp9);
    t_vec3 v = cross(&w, &u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
        camera->viewport_u = product_vec3_r(&u, camera->viewport_width);      // Vector across viewport horizontal edge
		t_vec3 neg_v = product_vec3_r(&v, -1);
        camera->viewport_v = product_vec3_r(&neg_v, camera->viewport_height);  // Vector down viewport vertical edge

		
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    camera->pixel_delta_u = division_vec3_r(&camera->viewport_u, img_w);
    camera->pixel_delta_v = division_vec3_r(&camera->viewport_v, img_h);

	/*
	        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
			auto viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
	*/

    // Calculate the location of the upper left pixel.
	t_vec3		tmp_focal = product_vec3_r(&w, camera->focal_length);
	t_vec3		half_view_u = division_vec3_r(&camera->viewport_u, 2);
	t_vec3		half_view_v = division_vec3_r(&camera->viewport_v, 2);

	t_vec3		center_viewport = substract_vec3(&camera->center, &tmp_focal);
	t_vec3		tmp = substract_vec3(&center_viewport, &half_view_u);
	t_point3	viewport_upper_left = substract_vec3(&tmp, &half_view_v);

	t_vec3		half_pixel = add_vec3(&camera->pixel_delta_u, &camera->pixel_delta_v);
	product_vec3(&half_pixel, 0.5);
	camera->pixel00_loc = add_vec3(&viewport_upper_left, &half_pixel);
}

