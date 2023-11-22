/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/11/22 12:54:00 by apriego-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*==============================	LIBRARIES	==============================*/

# include "libft.h"
# include "mlx.h"
# include "vec3.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>

/*=============================	ERROR MESSAGES	==============================*/

# define ERR_NO_MAP "Usage: [./miniRT] [your_map.rt]\n"
# define ERR_MISSING_RT_EXTENSION "Error: map doesn't have \
a valid extension *[.rt]\n"
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
	double			ratio;
	t_color			color;
	bool			init;
}					t_ambligth;

typedef struct s_camera
{
	t_point			center;
	t_vec3			dir;
	uint8_t			hfov;
	bool			init;
}					t_camera;

typedef struct s_ligth
{
	t_point				center;
	double				brigt;
	t_color				color;
	struct s_ligth		*next;
}						t_ligth;

typedef struct s_sphere
{
	t_point			center;
	double			radius;
	t_color			color;
}					t_sphere;

typedef struct s_plane
{
	t_point			center;
	t_vec3			dir;
	t_color			color;
}					t_plane;

typedef struct s_cylinder
{
	t_point			center;
	t_vec3			dir;
	double			radius;
	double			height;
	t_color			color;
}					t_cylinder;

typedef union u_objects
{
	t_cylinder		*cy;
	t_plane			*pl;
	t_sphere		*sp;
}					t_objects;

typedef struct s_world
{
	t_objects		type;
	void			(*hit)(t_objects);
	struct s_world	*next;
}					t_world;

typedef struct s_scene
{
	t_world			*objs;
	t_ligth			*ligth;
	t_ambligth		ambligth;
	t_camera		camera;
}					t_scene;

/*-------------------------------      MLX      ------------------------------*/

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
	void			*mlx;
	void			*mlx_win;
	t_image			img;
}					t_mlx;

/*==============================  FUNCTIONS  =============================*/
/*------------------------------  INIT_TOOL  -----------------------------*/

t_scene				init_structs(void);

/*------------------------------  INIT_OBJS  ------------------------------*/

int					check_sphere(t_scene *scene, char **split);
int					check_plane(t_scene *scene, char **split);
int					check_cylinder(t_scene *scene, char **split);
int					check_ligth(t_scene *scene, char **split);

/*----------------------------- INIT_STRUCTS -----------------------------*/

int					put_colors(t_color *colors, char *split);
int					put_coord(t_point *coord, char **coords);
int					put_dir(t_vec3 *dir, char **norm);
int					put_fov(uint8_t *hfov, char *num);

/*------------------------------  CHECK_ARG  -----------------------------*/

int					check_args(int argc, char **argv);
int					compare_str_end(char *str, char *end);
int					init_map(char *file, t_scene *scene);
int					fill_ambient(t_scene *scene, char **split);
int					fill_camera(t_scene *scene, char **split);
int					fill_light(t_ligth *ligth, char **split);
int					fill_sphere(t_sphere *sp, char **split);
int					fill_plane(t_plane *pl, char **split);
int					fill_cylinder(t_cylinder *cy, char **split);

/*------------------------------  UTILS  -------------------------------*/

void				init_image(t_mlx *data);
int					my_put_pixel(t_mlx *data, int x, int y, int color);
void				set_color(t_image *img, int pixel, int color);

#endif
