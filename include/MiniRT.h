/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:55:12 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/26 14:01:37 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*==============================	LIBRARIES	==============================*/

# include "libft.h"
# include "minilibx_ui.h"
# include "mlx.h"
# include "ray.h"
# include "vec3.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>

/*=============================	ERROR MESSAGES	==============================*/

# define ERR_NO_MAP "Usage: [./miniRT] [your_map.rt]\n"
# define ERR_MISSING_RT_EXTENSION \
	"Error: map doesn't have \
a valid extension *[.rt]\n"
# define ERR_INVALID_MAP "Error: invalid map format.\n"
# define ERR_OPENING_MAP "Error: Couldn't open map.\n"
# define ERR_CANVAS_SIZE "Error, canvas size range [200, 1500]\n"

/*=================================	MACROS	==================================*/

// COLOURS
# define GREENBASH "\033[1;38;2;180;235;31m"
# define NO_COL "\033[0m"
# define REDBASH "\033[1;38;2;255;0;0m"
// OBJECTS
# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"
# define CONE "cn"
// MLX
# define WIN_W 900
# define WIN_H 600
# define IMG_W WIN_W
# define IMG_H WIN_H
// KEYS
# define A_KEY 0x00
# define S_KEY 0x01
# define D_KEY 0x02
# define W_KEY 0x0D
# define M_KEY 0x2E
# define ONE_KEY 0x12
# define TWO_KEY 0x13
# define ESC_KEY 0x35
# define J_KEY 0x26
# define K_KEY 0x28
# define L_KEY 0x25
# define I_KEY 0x22
# define C_KEY 0x08
// HEXA COLOURS
# define WHITE 0xFFFFFF
# define GREEN 0x00E844
# define BLUE 0x10D663
# define BLACK 0x000000
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
# define MOVE 0.1
// UI
# define SM_PAD 25
# define MD_PAD 50
# define XL_PAD 100
// OTHERS
# define RAY_DEPTH 10
# define MIN_SIZE 0.000001
# define MAX_SIZE 1000000.0 
# define BIAS 0.00000001
//# define BIAS 0.00000000000001
# ifndef M_PI
#  define M_PI 3.1415926
# endif
// CHECKBOARD FACTOR
# define C_FACTOR 14
// HIT
# define H_CONE 0
# define H_DISK 1
# define H_CYLINDER 0
# define H_DISK_BA 1
# define H_DISK_TA 2

/*===============================	STRUCTURES	==============================*/

/*-------------------------------      MLX      ------------------------------*/

typedef struct s_image
{
	void			*ptr;
	int				pixel_bits;
	int				line_bytes;
	int				endian;
	char			*buffer;
}					t_image;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	t_image			img;
}					t_mlx;

/*-------------------------------      MAP      ------------------------------*/

typedef struct s_world	t_world;

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
	int				hfov;
	bool			init;
}					t_camera;

typedef struct s_light
{
	t_point3		center;
	t_color			color;
	double			bright;
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
	bool			hit[3];
}					t_cylinder;

typedef struct s_disk
{
	t_point3		center;
	t_vec3			dir;
	double			radius;
}					t_disk;

typedef struct s_cone
{
	t_point3		center;
	t_point3		apex;
	t_vec3			dir;
	double			angle;
	double			height;
	bool			hit[2];
}					t_cone;

typedef union u_objects
{
	t_cylinder		*cy;
	t_plane			*pl;
	t_sphere		*sp;
	t_cone			*cn;
}					t_objects;

typedef struct s_hit_record
{
	t_world			*obj;
	t_point3		p;
	t_vec3			normal;
	double			t;
	double			ray_tmin;
	double			ray_tmax;
}					t_hit;

typedef enum e_texture
{
	DEFAULT = 0,
	CHECKBOARD = 1,
	BITMAP = 2,
	BUMPMAP = 3,
	BITMAP_BUMPMAP = 4
}					t_texture;

typedef struct s_img_tex
{
	void			*img_ptr;
	char			*info;
	int				w;
	int				h;
	int				bpp;
	int				sl;
	int				endian;
}					t_img_tex;

typedef struct s_materia
{
	t_texture		texture;
	t_color			color;
	double			specular;
	double			roughness;
	double			metallic;
	t_img_tex		bit;
	t_img_tex		bump;
}					t_materia;

typedef struct s_matrix3x3{
	double			m[3][3];
}					t_matrix3x3;

typedef struct s_world
{
	t_objects		type;
	t_materia		materia;
	bool			(*hit)(const t_ray *, t_objects, t_hit *);
	void			(*free_type)(t_objects);
	t_vec3			*(*get_position_pointer)(t_objects *);
	t_color			(*get_color)(t_vec3 *, struct s_world *);
	t_color			(*get_normal_map)(t_vec3 *, struct s_world *);
	struct s_world	*next;
}					t_world;

typedef enum e_render_mode
{
	EDIT_MODE = 0,
	RAYTRACE_MODE = 1
}					t_render_mode;

typedef struct s_scene
{
	t_world			*objs;
	t_light			*light;
	t_amblight		amblight;
	t_camera		camera;
	t_world			*selected;
	int				*select_mask;
	t_color			bg_color;
	t_mlx			data;
	t_slider		slider;
	t_render_mode	render_mode;
}					t_scene;

typedef struct s_evars
{
	double			a;
	double			half_b;
	double			c;
	double			discriminant;
	double			root;
	double			sqrtd;
}					t_evars;

typedef struct s_uv
{
	double			u;
	double			v;
}					t_uv;

/*==============================  FUNCTIONS  =============================*/
/*------------------------------  INIT_TOOL  -----------------------------*/

void				init_structs(t_scene *scene);
int					check_dir(t_vec3 *dir);
void				inti_func_cylinder(t_world *cy);
void				inti_func_cone(t_world *cn);
int					check_materia(t_world *obj, char **split, int pos);

/*------------------------------  FREE_TOOL  -----------------------------*/

void				free_plane(t_objects obj);
void				free_sphere(t_objects obj);
void				free_cylinder(t_objects obj);
void				free_cone(t_objects obj);
void				free_structs(t_scene scene);

/*------------------------------ HIT_OBJECTS ------------------------------*/

bool				hit_cone(const t_ray *ray, t_objects obj, t_hit *rec);
bool				hit_sphere(const t_ray *ray, t_objects obj, t_hit *rec);
bool				hit_plane(const t_ray *ray, t_objects obj, t_hit *rec);
bool				hit_disk(const t_ray *ray, t_disk *obj, t_hit *rec);
bool				hit_cylinder(const t_ray *ray, t_objects obj, t_hit *rec);
bool				hit_disk_cone(const t_ray *ray, t_objects obj, t_hit *rec);

/*------------------------------ CHECKBOARD  ------------------------------*/

t_color				get_color_sphere(t_vec3 *p_hit, t_world *objs);
t_color				get_color_plane(t_vec3 *p_hit, t_world *objs);
t_color				get_color_cone(t_vec3 *p_hit, t_world *objs);
t_color				get_color_cylinder(t_vec3 *p_hit, t_world *objs);
t_uv				get_planar_map(t_point3 *p_hit, t_point3 *dir,
						t_point3 *center);
t_uv				get_spherical_map(t_point3 *p_hit, t_point3 *center,
						double radius);
t_uv				get_cylinder_map(t_point3 *p_hit, t_point3 *center, double radius);
t_uv				get_cone_map(t_point3 p_hit);
double				quit_decimals(double num);
t_color				checker_color(t_uv uv, t_color color);
t_matrix3x3			calculate_rotation_matrix(double angle, t_vec3 *axis);
t_vec3				rotate_point(t_vec3 *p, t_vec3 *center, t_matrix3x3 *r);
t_color				get_normal_map_sphere(t_vec3 *p_hit, t_world *obj);
t_color				get_normal_map_plane(t_vec3 *p_hit, t_world *obj);
t_color				map_uv_to_color(t_uv *uv, t_img_tex *img_tex);

/*------------------------------  INIT_OBJS  ------------------------------*/

int					check_sphere(t_scene *scene, char **split);
int					check_plane(t_scene *scene, char **split);
int					check_cylinder(t_scene *scene, char **split);
int					check_cone(t_scene *scene, char **split);
int					check_light(t_scene *scene, char **split);

/*----------------------------- INIT_STRUCTS -----------------------------*/

int					put_colors(t_color *colors, char *split);
int					put_coord(t_point3 *coord, char **coords);
int					put_dir(t_vec3 *dir, char **norm);
int					fill_cone(t_cone *cn, char **split);
int					put_fov(int *hfov, char *num);

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
int					key_down(int key, void *param);
int					mouse_up(int button, int x, int y, void *param);
int					mouse_down(int button, int x, int y, void *param);
int					mouse_move(int x, int y, void *param);
void				move_object(t_scene *scene, int key);
int					close_program(t_scene *scene, int exit_code);
void				update_slider(t_slider *slider, int x);

/*------------------------------  CAMERA  ------------------------------*/

void				render_image(t_scene *scene, int img_w, int img_h);
void				start_raytracer(t_mlx *data, t_scene *scene, int img_w,
						int img_h);
void				set_camera(t_camera *camera, int img_w, int img_h);
void				set_pixel00(t_camera *camera, t_vec3 *cam_axis);
t_world				*select_object(t_scene *scene, int x, int y);
t_world				*send_selector_ray(t_ray *r, t_scene *scene);
t_vec3				*get_position_sphere(t_objects *obj);
t_vec3				*get_position_cylinder(t_objects *obj);
t_vec3				*get_position_plane(t_objects *obj);
t_vec3				*get_position_cone(t_objects *obj);
t_color				render_edit_mode(t_scene *scene,
						const t_ray *r, t_hit *hit);
t_color				render_raytrace_mode(t_scene *scene, const t_ray *r,
						t_hit *hit_rec, int ray_depth);
t_color				send_ray(const t_ray *r, t_scene *scene, int i, int j);
void				calc_shadow_ray(t_ray *shadow_ray, t_light *lights,
						t_hit *hit_rec);
t_color				calc_ambient_light(t_color *ambient, t_color *obj,
						double ratio);
t_color				calc_diffuse_light(t_light *lights, t_ray *r_light,
						t_hit *hit_rec);
t_color				calc_specular_light(t_light *lights, const t_ray *r,
						t_ray *r_light, t_hit *hit_rec);
bool				calc_hard_shadows(t_world *objs, t_ray *r_light,
						t_hit *hit_rec);
t_color				calc_reflected_color(t_scene *scene, t_hit *hit_rec, const t_ray *r, int ray_depth);
void				draw_outlines(t_scene *scene);

/*------------------------------  UTILS  -------------------------------*/

double				clamp_number(double nb, int low_limit, int high_limit);
int					create_color(double a, double r, double g, double b);
double				deg_to_rad(double degree);
t_point3			ray_at(const t_ray *ray, double t);
void				draw_menu(t_scene *scene);
int					screen_object_center(t_scene *scene, double coord[2]);
void				my_string_put(t_mlx *data, int x, int y, char *txt);
double				ft_max(double nb, double limit);
t_slider			init_slider(int min_value, int max_value, int *value,
						uint16_t length);
void				draw_slider(void *mlx_ptr, void *mlx_win, t_slider *slider,
						int x, int y);
bool				is_within(int nb, int min, int max);

#endif
