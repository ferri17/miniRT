/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:34 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/18 11:56:56 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

# define X 0
# define Y 1
# define Z 2

# define R 0
# define G 1
# define B 2

struct	s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color;

/*------------------------------  VEC3_UTILS  -----------------------------*/

t_vec3		add_vec3(const t_vec3 *vector1, const t_vec3 *vector2);
t_vec3		substract_vec3(const t_vec3 *vector1, const t_vec3 *vector2);
void		product_vec3(t_vec3 *vector, double factor);
t_vec3		product_vec3_r(const t_vec3 *vector, double factor);
void		division_vec3(t_vec3 *vector, double factor);
t_vec3		division_vec3_r(const t_vec3 *vector, double factor);
double		dot(const t_vec3 *v1, const t_vec3 *v2);
t_vec3		cross(const t_vec3 *v1, const t_vec3 *v2);
double		length(const t_vec3 *vector);
double		length_squared(const t_vec3 *vector);
t_vec3		unit_vector(const t_vec3 *vector);
t_vec3		normal_vector(t_vec3 *vector, double old_range, double new_range);
t_vec3		vproduct_vec3(t_vec3 *v1, t_vec3 *v2);

#endif
