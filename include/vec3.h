/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:34 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/16 13:16:43 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# define X 0
# define Y 1
# define Z 2

# define R 0
# define G 1
# define B 2

struct	s_vec3
{
	double	e[3];
};

typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point;
typedef struct s_vec3	t_color;

#endif