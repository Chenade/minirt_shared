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
# include <stdint.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "structure.h"

# define WIDTH 940
# define HEIGHT 640
# define GUI_HEIGHT 190

# define STEP 5

# define CAM 0
# define LIGHT 1
# define AMB 2
# define SP 3
# define PL 4
# define CY 5
# define CO 6

# define PI 3.14159265358979

# define WHITE 0x00FFFFFF
# define BLUE 0x000060FF
# define RED 0x00FF2020
# define GREEN 0x0000FF00

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
void		get_cam_axes(t_objs *cam);
void		init_math(t_objs *obj);
void		update_math(t_objs *obj, t_data *d, t_vector p);
void		init_cyl(t_data *d, int index);
void		init_cone(t_data *d, int index);
void		init_sp(t_data *d, int index);
void		init_pl(t_data *d, int index);
void		init_cam(t_data *d, int index);
void		init_ambient(t_data *d, int index);
void		init_light(t_data *d, int index);
int			map_check_cam(t_data *d, char **line, int index);
int			map_check_ambient(t_data *d, char **line, int index);
int			map_check_light(t_data *d, char **line, int index);
int			map_check_sphere(t_data *d, char **line, int index);
int			map_check_plane(t_data *d, char **line, int index);
int			map_check_cylinder(t_data *d, char **line, int index);
int			map_check_cone(t_data *d, char **line, int index);

// collision.c
t_pixel		hit_sphere(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		hit_plane(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		hit_cylinder(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		hit_cone(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		hit_light(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		min_scaler(int i, t_pixel p1, t_pixel p2);
int			ray_tracing(t_data *d, int x, int y);

//shadows.c
void		check_inside_objs(t_data *d);
void		get_shadow(t_pixel *p, t_data *d);
t_pixel		sphere_shadow(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		plane_shadow(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		cylinder_shadow(struct s_objs *obj, struct s_data *d, t_vector p);
t_pixel		cone_shadow(struct s_objs *obj, struct s_data *d, t_vector p);
t_vector	put_ambient(t_pixel pixel, t_pixel *p, t_data *d);
void		put_diffuse(t_pixel pixel, t_pixel *p, t_data *d);

// keyboard.c
int			ft_move(t_data *d, t_objs *obj, int keysym);
int			ft_dir(t_data *d, t_objs *obj, int keysym);
int			ft_rotate_cam(t_objs *obj, int keycode);
int			key_sphere(t_data *d, int keysym);
int			key_plane(t_data *d, int keysym);
int			key_cylinder(t_data *d, int keysym);
int			key_cone(t_data *d, int keysym);
int			key_camera(t_data *d, int keysym);
int			key_light(t_data *d, int keysym);
int			key_saved(t_data *d);

// print.c
char		*ft_putdouble_fd2(double d, int fd);
void		print_vector(t_vector v, int fd, int isnormal);
void		print_color(t_color c, int fd);
void		print_sphere(t_data *d, int index, int fd);
void		print_plane(t_data *d, int index, int fd);
void		print_cylinder(t_data *d, int index, int fd);
void		print_cone(t_data *d, int index, int fd);
void		print_camera(t_data *d, int index, int fd);
void		print_light(t_data *d, int index, int fd);
void		print_ambient(t_data *d, int index, int fd);

// draw_gui.c
void		mlx_putstr(t_data *d, int x, int y, char *str);
int			draw_gui(t_data *d);
void		gui_sphere(t_data *d, t_objs obj, int x);
void		gui_plane(t_data *d, t_objs obj, int x);
void		gui_cylinder(t_data *d, t_objs obj, int x);
void		gui_cone(t_data *d, t_objs obj, int x);
void		gui_camera(t_data *d, t_objs obj, int x);
void		gui_light(t_data *d, t_objs obj, int x);
void		gui_ambient(t_data *d, t_objs obj, int x);
void		print_move_menu(t_data *d, char *n_type, int type);
void		print_complete_menu(t_data *d, char *n_type, int type);
void		print_cam_menu(t_data *d);
void		print_menu(t_data *d);
void		mlx_putstr(t_data *d, int x, int y, char *str);
void		mlx_putstr_r(t_data *d, int x, int y, char *str);
void		mlx_putstr_g(t_data *d, int x, int y, char *str);
void		mlx_putstr_b(t_data *d, int x, int y, char *str);
void		draw_line(t_data *d, int x, int y, int l);
void		draw_column(t_data *d, int x, int y, int l);
void		put_rect(t_data *d, t_vector p, int w, int h);
void		paint_image(t_img *img, int color, int target);

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
int			check_inside_cy(t_objs *obj, t_vector p);
double		quadratic_discriminant(double a, double b, double c);
double		quadratic_solve(double a, double b, double c, t_objs *obj);
double		check_solutions_cy(t_objs *obj, t_data *d, t_vector p);
double		calculate_scaler_cy(t_objs *obj, t_data *d, t_vector p);
double		calculate_scaler_cy_maha(t_objs *obj, t_data *d, t_vector p);
double		smallest_visible_positive_cyl(t_objs *obj, t_data *d, t_vector p, \
			t_math m);
t_vector	calculate_cyl_normal(t_objs *cyl, t_vector hit_point);

//math_sp.c
int			check_inside_sp(t_objs *obj, t_vector p);
double		check_solutions(t_objs *obj, t_data *d, t_vector p);
double		calculate_scaler_sp(t_objs *obj, t_data *d, t_vector p);
t_vector	calculate_sp_normal(t_vector center, t_vector hit_point);

//math_pl.c
int			check_side_pl(t_objs *obj, t_vector p);
double		check_vn(t_objs *obj, t_data *d, double x, double y);
double		check_vn2(t_objs *obj, t_data *d);
double		calculate_scaler_pl(t_objs *obj, t_data *d, double x, double y);
double		calculate_scaler_pl2(t_objs *obj, t_data *d, t_vector p);

//math_co.c
int			check_inside_co(t_objs *obj, t_vector p);
double		smallest_visible_positive_co(t_objs *obj, t_data *d, t_vector p, \
			t_math m);
void		cone_math(t_data *d, t_objs *obj, t_vector p);
double		limit_cone(t_objs *obj, t_data *d, t_vector p, double t);
void		quadratic_solve_cyl_co(t_data *d, t_objs *obj, t_vector p);
double		calculate_scaler_co(t_objs *obj, t_data *d, t_vector p);
t_vector	calculate_cone_normal(t_objs *cone, t_vector hit_pt);

//vectors.c
void		print_vec(t_vector v);
int			compare_vecs(t_vector v, t_vector w);
void		rot_v_around_v(t_vector *v, t_vector *w, double angle);
t_vector	vector(double x, double y, double z);
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
void		img_pix_put(t_img *img, int x, int y, int color);
void		img_pix_darken(t_data *d, int x, int y, double amount);
int			getpixelcolor(t_img *img, int x, int y);
int			encode_rgb(t_color c);
int			init_vector(t_vector *v, int x, int y, int z);
void		get_cam_len(t_data *d);
#endif
