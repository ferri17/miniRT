/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:34 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/30 18:43:33 by fbosch           ###   ########.fr       */
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

/* struct	s_color
{
	int	c[3];
};

typedef struct s_color	t_color; */

/*------------------------------  VEC3_UTILS  -----------------------------*/

t_vec3	add_vec3(const t_vec3 *vector1, const t_vec3 *vector2);
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



/* t_vec3		add_vec3(t_vec3 vector1, t_vec3 vector2);
t_vec3		substract_vec3(t_vec3 vector1, t_vec3 vector2);

void		product_vec3(t_vec3 *vector, double factor);
t_vec3		product_vec3_r(t_vec3 vector, double factor);
void		division_vec3(t_vec3 *vector, double factor);
t_vec3		division_vec3_r(t_vec3 vector, double factor);

double		dot(t_vec3 v1, t_vec3 v2);
t_vec3		cross(t_vec3 v1, t_vec3 v2);
double		length(t_vec3 vector);
double		length_squared(t_vec3 vector);
t_vec3		unit_vector(t_vec3 vector); */

#endif
