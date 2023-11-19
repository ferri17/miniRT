/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/19 01:25:30 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*==============================	LIBRARIES	==============================*/

# include <fcntl.h>
# include "libft.h"
# include "vec3.h"
# include "mlx.h"
# include <stdbool.h>
# include <math.h>
# include <limits.h>

/*=============================	ERROR MESSAGES	==============================*/

# define ERR_NO_MAP "Usage: [./miniRT] [your_map.rt]\n"
# define ERR_MISSING_RT_EXTENSION "Error: map doesn't have a valid extension *[.rt]\n"
# define ERR_INVALID_MAP "Error: invalid map format.\n"
# define ERR_OPENING_MAP "Error: Couldn't open map.\n"

/*=================================	MACROS	==================================*/

// Colours
# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"
// Inentity
# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"
// MLX
# define WIN_W 1400
# define WIN_H 750
# define PAD 50
// KEYS
# define ESC_KEY 0x35
/*###	X11 EVENTS SUPPORTED BY MINILIBX	###*/
# define KEYDOWN 2
# define KEYUP 3
# define MOUSEDOWN 4
# define MOUSEUP 5
# define MOUSEMOVE 6
# define EXPOSE 12
# define DESTROY 17

/*===============================	STRUCTURES	==============================*/

/*-------------------------------      MAP      ------------------------------*/

typedef struct s_ambligth
{
	double				ratio;
	t_color				color;
	bool				init;
}						t_ambligth;

typedef struct s_camera
{
	t_point				center;
	t_vec3				dir;
	int					fov;
	bool				init;
}						t_camera;

typedef struct s_ligth
{
	t_point				center;
	double				brigt;
	t_color				color;
}						t_ligth;

typedef struct s_sphere
{
	t_point				center;
	double				radius;
	t_color				color;
}						t_sphere;

typedef struct s_plane
{
	t_point				center;
	t_vec3				dir;
	t_color				color;
}						t_plane;

typedef struct s_cylinder
{
	t_point				center;
	t_vec3				dir;
	double				radius;
	double				height;
	t_color				color;
}						t_cylinder;

typedef union u_objects
{
	t_cylinder			*cy;
	t_plane				*pl;
	t_sphere			*sp;
}						t_objects;

typedef struct s_objs_clas
{
	t_objects			type;
	void				(*hit)(t_objects);
	struct s_objs_clas	*next;
}						t_obj_class;

typedef struct s_scene
{
	t_obj_class			*objs;
	t_ligth				ligth;
	t_ambligth			ambligth;
	t_camera			camera;
}						t_scene;

/*-------------------------------      MLX      ------------------------------*/

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
}				t_mlx;

/*==============================  FUNCTIONS  =============================*/
/*------------------------------  INIT_TOOL  -----------------------------*/

t_scene					init_structs(void);
t_mlx					init_mlx(void);

/*------------------------------  INIT_OBJS  ------------------------------*/

int						check_sphere(t_scene *scene, char **split);
int						check_plane(t_scene *scene, char **split);
int						check_cylinder(t_scene *scene, char **split);

/*----------------------------- INIT_STRUCTS -----------------------------*/

int						put_colors(t_color *colors, char *split);
int						put_coord(t_point *coord, char **coords);
int						put_dir(t_vec3 *dir, char **norm);
int						put_fov(int *fov, char *num);

/*------------------------------  CHECK_ARG  -----------------------------*/

int						check_args(int argc, char **argv);
int						compare_str_end(char *str, char *end);
int						init_map(char *file, t_scene *scene);
int						fill_ambient(t_scene *scene, char **split);
int						fill_camera(t_scene *scene, char **split);
int						fill_light(t_scene *scene, char **split);
int						fill_sphere(t_sphere *sp, char **split);
int						fill_plane(t_plane *pl, char **split);
int						fill_cylinder(t_cylinder *cy, char **split);

#endif
