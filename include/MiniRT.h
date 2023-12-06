/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/06 16:42:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*==============================	LIBRARIES	==============================*/

# include "libft.h"
# include "mlx.h"
# include "vec3.h"
# include "ray.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>

#include <stdio.h> //BORRAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAR

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
# define WIN_W 900
# define WIN_H 506
# define IMG_W WIN_W
# define IMG_H WIN_H
// KEYS
# define A_KEY		0x00
# define S_KEY		0x01
# define D_KEY		0x02
# define W_KEY		0x0D
# define M_KEY		0x2E
# define ONE_KEY	0x12
# define TWO_KEY	0x13
# define ESC_KEY	0x35
# define J_KEY		0x26
# define K_KEY		0x28
# define L_KEY		0x25
# define I_KEY		0x22
// MOUSE EVENTS
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MID_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5
// X11 EVENTS SUPPORTED BY MINILIBX
# define KEYDOWN 2
# define KEYUP 3
# define MOUSEDOWN 4
# define MOUSEUP 5
# define MOUSEMOVE 6
# define EXPOSE 12
# define DESTROY 17
// GENERAL DEFINITIONS
# define MOVE 0.05

/*===============================	STRUCTURES	==============================*/

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
}	t_mlx;

/*-------------------------------      MAP      ------------------------------*/

typedef struct s_amblight
{
	double			ratio;
	t_color			color;
	bool			init;
}					t_amblight;

typedef struct s_camera
{
	t_point3		center;
	t_point3		pixel00_loc;
	double			focal_length;
	double			viewport_height;
	double			viewport_width;
    t_vec3			viewport_u;
    t_vec3			viewport_v;
    t_vec3			pixel_delta_u;
    t_vec3			pixel_delta_v;
	t_vec3			vup;
	t_vec3			dir;
	uint8_t			hfov;
	bool			init;
}					t_camera;

typedef struct s_light
{
	t_point3		center;
	double			bright;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct s_sphere
{
	t_point3		center;
	double			radius;
}					t_sphere;

typedef struct s_plane
{
	t_point3		center;
	t_vec3			normal;
}					t_plane;

typedef struct s_cylinder
{
	t_point3		center;
	t_vec3			dir;
	double			radius;
	double			height;
}					t_cylinder;

typedef union u_objects
{
	t_cylinder		*cy;
	t_plane			*pl;
	t_sphere		*sp;
}					t_objects;

typedef struct	s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	double		ray_tmin;
	double		ray_tmax;
}	t_hit;

typedef struct s_world
{
	t_objects		type;
	t_color			color; // MATERIAAAAAAAAAAAL
	bool			(*hit)(const t_ray *, t_objects, t_hit *);
	void			(*move)(t_objects *, t_vec3 *move);
	struct s_world	*next;
}					t_world;

enum	render_mode
{
	EDIT_MODE = 0,
	RAYTRACE_MODE = 1
};

typedef struct s_scene
{
	t_world				*objs;
	t_light				*light;
	t_amblight			amblight;
	t_camera			camera;
	t_world				*selected;
	t_mlx				data;
	enum render_mode	render_mode;
}					t_scene;

/*==============================  FUNCTIONS  =============================*/
/*------------------------------  INIT_TOOL  -----------------------------*/

void				init_structs(t_scene *scene);

/*------------------------------  INIT_OBJS  ------------------------------*/

int					check_sphere(t_scene *scene, char **split);
int					check_plane(t_scene *scene, char **split);
int					check_cylinder(t_scene *scene, char **split);
int					check_light(t_scene *scene, char **split);

/*----------------------------- INIT_STRUCTS -----------------------------*/

int					put_colors(t_color *colors, char *split);
int					put_coord(t_point3 *coord, char **coords);
int					put_dir(t_vec3 *dir, char **norm);
int					put_fov(uint8_t *hfov, char *num);

/*------------------------------  CHECK_ARG  -----------------------------*/

int					check_args(int argc, char **argv);
int					compare_str_end(char *str, char *end);
int					init_map(char *file, t_scene *scene);
int					fill_ambient(t_scene *scene, char **split);
int					fill_camera(t_scene *scene, char **split);
int					fill_light(t_light *scene, char **split);
int					fill_sphere(t_sphere *sp, char **split);
int					fill_plane(t_plane *pl, char **split);
int					fill_cylinder(t_cylinder *cy, char **split);

/*------------------------------  MINILIBX  -------------------------------*/

void				init_mlx_windows(t_mlx *data, int win_w, int win_h);
void				init_mlx_image(t_mlx *data, int img_w, int img_h);
int					my_put_pixel(t_mlx *data, int x, int y, int color);
void				set_color(t_image *img, int pixel, int color);
int					close_program(t_scene *scene, int exit_code);
int					key_down(int key, void *param);
int					mouse_up(int button, int x, int y, void *param);
void				move_object(t_scene *scene, int key);
void				change_render_mode(t_scene *scene);

/*------------------------------  CAMERA  ------------------------------*/

void				render_image(t_scene *scene, int img_w, int img_h);
void				start_raytracer(t_mlx *data, t_scene *scene, int img_w, int img_h);
void				set_camera(t_camera *camera, int img_w, int img_h);
void				set_pixel00(t_camera *camera, t_vec3 *cam_axis);
bool				hit_sphere(const t_ray *ray, t_objects obj, t_hit *rec);
bool				hit_plane(const t_ray *ray, t_objects obj, t_hit *rec);
bool				hit_cylinder(const t_ray *ray, t_objects obj, t_hit *hit_record);
t_world				*select_object(t_scene *scene, int x, int y);
t_world				*send_selector_ray(t_ray *r, t_scene *scene);
void				move_sphere(t_objects *obj, t_vec3 *move);
void				move_cylinder(t_objects *obj, t_vec3 *move);
void				move_plane(t_objects *obj, t_vec3 *move);
t_color				render_edit_mode(t_scene *scene, t_world *objs, const t_ray *r, t_hit *hit);
t_color				render_raytrace_mode(t_scene *scene, t_world *hit_obj, t_hit*tmp_hit);

/*------------------------------  UTILS  -------------------------------*/

double				clamp_number(double nb, int low_limit, int high_limit);
int					create_color(int a, int r, int g, int b);
double				deg_to_rad(double degree);
t_point3			ray_at(const t_ray *ray, double t);
void				draw_menu(t_scene *scene);

#endif
