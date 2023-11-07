/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/07 12:46:20 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*==============================	LIBRARIES	==============================*/

# include "libft.h"

/*=================================	MACROS	==================================*/

// Colours
# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"

/*===============================	STRUCTURES	==============================*/

typedef struct s_colors
{
	int	R;
	int	G;
	int	B;
}	t_colors;

typedef struct s_coords
{
	int	X;
	int	Y;
	int	Z;
}	t_coords;

typedef struct s_direction
{
	float	X;
	float	Y;
	float	Z;
}	t_direction;

typedef struct s_ambientligth //Seguramente sera una lista pero bueno
{
	float		ratio;
	t_colors	color;
}	t_ligth;

 //esta en concreto es la unica que no tiene sentido que sea un 
 //lista por el echo de que no tiene sentido mas de una camera
typedef struct s_camera
{
	t_coords	coord;
	t_direction	direct;
	int			fov;
}	t_camera;

typedef struct s_ligth //Seguramente sera una lista pero bueno
{
	t_coords	coord;
	float		brigt;
	t_colors	color;
}	t_ligth;

typedef struct s_sphere
{
	t_coords	coord;
	float		diam;
	t_colors	colors;
	struct s_sphere *next;
}	t_sphere;

typedef struct s_plane
{
	t_coords	coord;
	t_direction	direct;
	t_colors	colors;
	struct s_plane *next;
}	t_plane;

typedef struct s_cylinder
{
	t_coords	coord;
	t_direction	direct;
	float		diameter;
	float		height;
	t_colors	colors;
	struct s_cylinder *next;
}	t_cylinder;

typedef struct s_objects
{

}	t_objects;

/*==============================  FUNCTIONS  =============================*/

int check_args(int argc, char **argv);

#endif
