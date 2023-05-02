/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:35:09 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/17 19:35:09 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	norm;
}	t_vector;

typedef struct s_pixel
{
	int			is_light;
	double		scaler;
	t_color		color;
	t_vector	dir;
	t_vector	normal;
	t_vector	pos;
}	t_pixel;

typedef struct s_math
{
	double		a;
	double		b;
	double		c;
	double		radius_2;
	double		vs;
	double		w;
	double		h0;
	double		w_2;
	double		rh_2;
	double		s1;
	double		s2;
	double		s_base;
	t_vector	base_normal;
	t_vector	va;
	t_vector	ra;
}	t_math;

typedef struct s_data	t_data;

typedef struct s_img
{
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_len;
	char	*addr;
	void	*mlx_img;
}	t_img;

typedef struct s_objs
{
	int			type;
	int			cam_is_inside;
	int			from_light;
	t_color		color;
	t_vector	pos;
	t_vector	dir;
	t_vector	dir_y;
	t_vector	dir_x;
	t_vector	normal;
	t_vector	cap_1;
	t_vector	cap_2;
	double		height;
	double		radius;
	double		radius_2;
	double		intensity;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		cone_angle;
	void		*collision_func;
	void		*shadow_func;
	void		*keyboard_func;
	void		*gui_func;
	void		*print_func;
	t_math		math;
	t_img		icon;
}	t_objs;

typedef struct s_data
{
	void			*win_ptr;
	void			*mlx_ptr;
	t_img			img;
	t_img			menu_back;
	int				display_gui;
	int				rec_col;
	int				img_changed;

	double			fov;
	double			cam_len;
	int				index;

	char			**raw;
	int				nbr_objs;
	int				nbr_camera;
	int				nbr_light;
	int				nbr_ambient;
	t_pixel			cur_p;
	struct s_objs	*objs;
	struct s_objs	*cam;
	struct s_objs	*light;
	struct s_objs	*ambient;
}	t_data;

#endif