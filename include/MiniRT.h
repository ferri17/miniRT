/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/14 15:53:45 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*==============================	LIBRARIES	==============================*/

# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include <stdbool.h>
# include <math.h>
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
// NO SE
# define X 0
# define Y 1
# define Z 2
/*###	MAP THEMES	###*/
# define BG_C 0
# define OBJ1_C 1
# define OBJ2_C 2
# define TEXT 3
# define CUBE_VERTEX 8
typedef struct s_point
{
	float		axis[3];
	int			color;
}				t_point;

typedef struct s_line
{
	t_point		start;
	t_point		end;
}				t_line;

typedef struct s_line_draw
{
	int			start[2];
	int			end[2];
}				t_line_draw;

typedef struct s_bresenh
{
	t_line_draw	draw;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
	bool		accept;
}				t_bresenh;

typedef struct s_key
{
	bool		right_clicked;
	bool		first_right_click;
	bool		left_clicked;
	bool		first_left_click;
	bool		axis_locked[3];
}				t_key;

typedef struct rotation_matrix
{
	float		x[3][3];
	float		y[3][3];
	float		z[3][3];
}				t_mtx;

typedef struct s_map
{
	int			fd;
	int			x_size;
	int			y_size;
	int			size;
	int			highest;
	int			lowest;
	int			theme[4];
	int			col_axis[3];
	double		zoom;
	float		z_resize;
	float		translate[2];
	int			rotate[3];
	t_mtx		r_matrix;
	uint8_t		mode;
	int			t_render;
	t_line		line;
	t_point		*terrain;
	t_point		*obj;
}				t_map;

typedef struct s_image
{
	void		*ptr;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	char		*buffer;
}				t_image;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_map		map;
	t_image		img;
	t_key		key;
}				t_mlx;

/*===============================	STRUCTURES	==============================*/

/*-------------------------------      MAP      ------------------------------*/

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

/*-------------------------------      MLX      ------------------------------*/


/*
typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_image		img;
}				t_mlx;*/

/*==============================  FUNCTIONS  =============================*/
/*------------------------------  INIT_TOOL  -----------------------------*/

t_scene					init_structs(void);
t_mlx					init_mlx(void);

/*------------------------------  INIT_OBJS  ------------------------------*/

int						check_sphere(t_scene *scene, char **split);
int						check_plane(t_scene *scene, char **split);
int						check_cylinder(t_scene *scene, char **split);

/*----------------------------- INIT_STRUCTS -----------------------------*/

int						put_colors(t_colors *colors, char *split);
int						put_coord(t_coords *coord, char **coords);
int						put_direct(t_direction *direct, char **norm);
int						put_fov(int *fov, char *num);

/*------------------------------  CHECK_ARG  -----------------------------*/

int						check_args(int argc, char **argv);
int						check_map(char *file, t_scene *scene);
int						fill_ambient(t_scene *scene, char **split);
int						fill_camera(t_scene *scene, char **split);
int						fill_light(t_scene *scene, char **split);
int						fill_sphere(t_sphere *sp, char **split);
int						fill_plane(t_plane *pl, char **split);
int						fill_cylinder(t_cylinder *cy, char **split);

/*---------------------*//*---------------------*//*---------------------*//*---------------------*//*---------------------*/
void	bresenham(t_mlx *data, t_line line);
void	draw_extras(t_mlx *data);

#endif
