/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:14:04 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:14:05 by ykuo             ###   ########.fr       */
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

# define WIDTH 1600
# define HEIGHT 1200

# define BASE "0123456789abcdef"

# define COLOR_WHITE 0x00FFFFFF
# define COLOR_TEXT 0xEAEAEA

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
	int	c;
}	t_vector;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_data
{
	void		*win_ptr;
	void		*mlx_ptr;
	t_img		img;
	char		*buf;
	int			size;
	t_vector	*u;
	t_vector	*v;
	int			w;
	int			h;

	int			map_h;
	int			map_w;
	char		**map;
	t_vector	**map_3d;
	t_vector	**map_2d;
	int			line_length;
	int			height;
	int			height2;
	t_vector	*center;
	t_vector	*rot;
	int			projection;
}	t_data;

// main.c
int			fdf(char *filename);

// init.c
int			init_map(t_data *d);
int			init_setup(t_data *d);
int			init_var(t_data *d);

//mlx_setup.c
int			init_mlx(t_data *d);
int			render_frame(t_data *d);
void		draw_imgs(t_data *d);
int			handle_exit(t_data *data);
int			handle_keypress(int keysym, t_data *data);

// parse.c
int			map_width(t_data *d, char **line);
int			read_file(t_data *d, char *name);
int			init_map(t_data *d);
int			init_var(t_data *d);

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

// tools.c
void		img_pix_put(t_data *d, int x, int y, int color);
int			getpixelcolor(t_img *img, int x, int y);
int			encode_rgb(t_color c);
int			xy_to_x(t_data *d, int x, int y);
int			init_vector(t_vector *v, int x, int y, int z);
#endif
