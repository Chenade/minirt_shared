/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:33:05 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/17 19:33:06 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "structure.h"

# define WIDTH 1080
# define WIN_HEIGHT 840
# define HEIGHT 640
# define GUI_HEIGHT 700

# define STEP 5

# define DEF 0
# define PL 1
# define SP 2
# define CYL 3
# define CO	4

# define PI 3.14159265358979

# define COLOR_WHITE 0x00FFFFFF
# define COLOR_TEXT 0x202020

// setup.c
int			set_vector(t_vector *v, char *str);
int			set_dir(t_vector *v, char *str);
int			set_color(t_color *c, char *str);

//mlx_setup.c
int			init_mlx(t_data *d);
int			render_frame(t_data *d);
void		draw_imgs(t_data *d);
int			handle_exit(t_data *data);
int			handle_keypress(int keysym, t_data *data);

// parse.c
int			read_file(t_data *d, char *name);
void		init_math(t_objs *obj);
int			map_check_cam(t_data *d, char **line, int index);
int			map_check_ambient(t_data *d, char **line, int index);
int			map_check_light(t_data *d, char **line, int index);
int			map_check_sphere(t_data *d, char **line, int index);
int			map_check_plane(t_data *d, char **line, int index);
int			map_check_cylinder(t_data *d, char **line, int index);

// collision.c
t_pixel		hit_sphere(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		hit_plane(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		hit_cylinder(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		hit_light(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		min_scaler(int i, t_pixel p1, t_pixel p2);
int			ray_tracing(t_data *d, int x, int y);

//shadows.c
void		get_shadow(t_pixel *p, t_data *d);
t_pixel		sphere_shadow(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		plane_shadow(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		cylinder_shadow(struct s_objs *obj, struct s_data *d, t_vector p);
void		get_color(t_pixel pixel, t_pixel *p, t_data *d);

// keyboard.c
int			ft_move(t_objs *obj, int keysym);
int			ft_dir(t_objs *obj, int keysym);
int			key_sphere(t_data *d, int keysym);
int			key_plane(t_data *d, int keysym);
int			key_cylinder(t_data *d, int keysym);
int			key_camera(t_data *d, int keysym);
int			key_light(t_data *d, int keysym);
int			key_saved(t_data *d);

// print.c
void		print_vector(t_vector v, int fd, int isnormal);
void		print_color(t_color c, int fd);
void		print_sphere(t_data *d, int index, int fd);
void		print_plane(t_data *d, int index, int fd);
void		print_cylinder(t_data *d, int index, int fd);
void		print_camera(t_data *d, int index, int fd);
void		print_light(t_data *d, int index, int fd);
void		print_ambient(t_data *d, int index, int fd);

// draw_gui.c
void		mlx_putstr(t_data *d, int x, int y, char *str);
int			draw_gui(t_data *d);
void		gui_sphere(t_data *d, t_objs obj, int x);
void		gui_plane(t_data *d, t_objs obj, int x);
void		gui_cylinder(t_data *d, t_objs obj, int x);
void		gui_camera(t_data *d, t_objs obj, int x);
void		gui_light(t_data *d, t_objs obj, int x);
void		gui_ambient(t_data *d, t_objs obj, int x);

// general.c
void		free_data(t_data *d);
void		print_err(const char *err_msg, t_data *d);
int			check_filename(const char *name, const char *ext);

//helper.c
long int	findSize(char file_name[]);
void		print_img_data(t_img *i);
int			print_info(char *name);
void		*ft_malloc(t_data *d, size_t size);

//math_cy.c
double		quadratic_discriminant(double a, double b, double c);
double		quadratic_solve(double a, double b, double c);
double		check_solutions_cy(t_objs *obj, t_data *d, t_vector p);
double		calculate_scaler_cy(t_objs *obj, t_data *d, t_vector p);
double		calculate_scaler_cy_maha(t_objs *obj, t_data *d, t_vector p);
t_vector	calculate_cyl_normal(t_objs *cyl, t_vector hit_point);

//math_sp.c
double		check_solutions(t_objs *obj, t_data *d, t_vector p);
double		calculate_scaler_sp(t_objs *obj, t_data *d, t_vector p);
t_vector	calculate_sp_normal(t_vector center, t_vector hit_point);

//math_pl.c
double		check_vn(t_objs *obj, t_data *d, double x, double y);
double		check_vn2(t_objs *obj, t_data *d);
double		calculate_scaler_pl(t_objs *obj, t_data *d, double x, double y);
double		calculate_scaler_pl2(t_objs *obj, t_data *d, t_vector p);

//vectors.c
int			init_vector(t_vector *v, int x, int y, int z);
double		get_norm(double x, double y, double z);
double		get_vec_norm(t_vector v);
t_vector	cross_product(t_vector v1, t_vector v2);
double		dot_product(t_vector v1, t_vector v2);
t_vector	normalize_vect(t_vector v);
void		get_cur_vec(t_data *d, int x, int y);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_sum(t_vector v1, t_vector v2);
t_vector	vec_fact(t_vector v1, t_vector v2);
t_vector	vec_scale(t_vector w, double scaler);

// tools.c
double		smallest_positive(double n1, double n2);
void		img_pix_put(t_data *d, int x, int y, int color);
int			getpixelcolor(t_img *img, int x, int y);
int			encode_rgb(t_color c);
int			init_vector(t_vector *v, int x, int y, int z);
void		get_cam_len(t_data *d);
#endif
