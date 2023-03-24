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
# define HEIGHT 640

# define PL 0
# define SP 1
# define CYL 2
# define CO	3

# define PI 3.14159265358979

# define BASE "0123456789abcdef"

# define COLOR_WHITE 0x00FFFFFF
# define COLOR_TEXT 0xEAEAEA

// main.c
int			fdf(char *filename);

// init.c
int			init_map(t_data *d);
int			init_setup(t_data *d);
int			init_var(t_data *d);
int			set_vector(t_vector *v, char *str);
int			set_orientation(t_vector *v, char *str);
int			set_color(t_color *c, char *str);

//mlx_setup.c
int			init_mlx(t_data *d);
int			render_frame(t_data *d);
void		draw_imgs(t_data *d);
int			handle_exit(t_data *data);
int			handle_keypress(int keysym, t_data *data);

// parse.c
int			map_width(t_data *d, char **line);
int			read_file(t_data *d, char *name);
int			map_check_cam(t_data *d, char **line, int index);
int			map_check_ambient(t_data *d, char **line, int index);
int			map_check_light(t_data *d, char **line, int index);
int			map_check_sphere(t_data *d, char **line, int index);
int			map_check_plane(t_data *d, char **line, int index);
int			map_check_cylinder(t_data *d, char **line, int index);

int			init_map(t_data *d);
int			init_var(t_data *d);

// collision.c
t_pixel		hit_sphere(struct s_objs *obj, struct s_data *d, int x, int y);
t_pixel		hit_plane(struct s_objs *obj, struct s_data *d, int x, int y);
t_pixel		hit_cylinder(struct s_objs *obj, struct s_data *d, int x, int y);
int			ray_tracing(t_data *d, int x, int y);

// draw.c
void		ft_lines_draw(t_data *d, t_vector f, t_vector s);
int			draw_gui(t_data *d);
void		draw_maps(t_data *d);
void		projection_isometric(t_data *d);
void		projection_first_angel(t_data *d);

// matrix.c
int			ft_matrix_rotate(t_data *d, int i);
int			ft_matrix_to_vector(t_data *d, int i);
int			ft_matrix_iter(t_data *d);
int			ft_matrix_move(t_data *d, t_vector min, t_vector max);
int			ft_matrix_center(t_data *d);

// general.c
void		free_cord_map(t_data *d);
void		free_data(t_data *d);
void		print_err(const char *err_msg, t_data *d);
int			check_filename(const char *name, const char *ext);

//helper.c
long int	findSize(char file_name[]);
void		print_img_data(t_img *i);
int			print_info(char *name);
int			print_map(t_data *d, t_vector **map);
void		*ft_malloc(t_data *d, size_t size);

//math.c
double		check_solutions(t_objs *obj, t_data *d, double x, double y);
double		calculate_time(t_objs *obj, t_data *d, double x, double y);

// tools.c
void		img_pix_put(t_data *d, int x, int y, int color);
int			getpixelcolor(t_img *img, int x, int y);
int			encode_rgb(t_color c);
int			xy_to_x(t_data *d, int x, int y);
int			init_vector(t_vector *v, int x, int y, int z);
void		get_cam_len(t_data *d);
#endif
