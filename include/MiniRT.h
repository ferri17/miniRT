/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/13 16:12:51 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*==============================	LIBRARIES	==============================*/

# include "fcntl.h"
# include "libft.h"

/*=================================	MACROS	==================================*/

// Colours
# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"
# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"

/*===============================	STRUCTURES	==============================*/

typedef struct s_colors
{
	int					r;
	int					g;
	int					b;
}						t_colors;

typedef struct s_coords
{
	int					x;
	int					y;
	int					z;
}						t_coords;

typedef struct s_direction
{
	double				x;
	double				y;
	double				z;
}						t_direction;

typedef struct s_ambligth
{
	double				ratio;
	t_colors			color;
}						t_ambligth;

typedef struct s_camera
{
	t_coords			coord;
	t_direction			direct;
	int					fov;
}						t_camera;

typedef struct s_ligth
{
	t_coords			coord;
	double				brigt;
	t_colors			color;
}						t_ligth;

typedef struct s_sphere
{
	t_coords			coord;
	double				radius;
	t_colors			colors;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	t_coords			coord;
	t_direction			direct;
	t_colors			colors;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	t_coords			coord;
	t_direction			direct;
	double				radius;
	double				height;
	t_colors			colors;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_objects
{
	t_cylinder			*cy;
	t_plane				*pl;
	t_sphere			*sp;
}						t_objects;

typedef struct s_scene
{
	t_objects			objs;
	t_ligth				ligth;
	t_ambligth			ambligth;
	t_camera			camera;
}						t_scene;

/*==============================  FUNCTIONS  =============================*/
/*------------------------------  INIT_TOOL  -----------------------------*/

t_scene					init_structs(void);

/*------------------------------  CHECK_ARG  -----------------------------*/

int						check_args(int argc, char **argv);
int						check_map(char *file, t_scene *scene);
int						fill_ambient(t_scene *scene, char **split);
int						fill_camera(t_scene *scene, char **split);

#endif
