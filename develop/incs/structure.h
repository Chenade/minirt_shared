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
}	t_vector;

typedef struct s_pixel
{
	int			is_light;
	t_vector	pos;
	t_vector	norm;
	t_color		color;
	double		scaler;
}	t_pixel;

typedef struct s_data	t_data;

typedef struct s_objs
{
	int			type;
	void		*collision_func;
	void		*keyboard_func;
	t_vector	cord;
	t_vector	orientation;
	t_color		color;
	double		ratio;
	double		diameter;
	double		height;
}	t_objs;

typedef struct s_cam
{
	double		fov;
	double		cam_len;
	t_vector	cord;
	t_vector	orientation;
}	t_cam;

typedef struct s_light
{
	t_vector	pos;
	double		ratio;
	t_color		color;
}	t_light;

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
	void			*win_ptr;
	void			*mlx_ptr;
	t_img			img;

	// double			fov;
	// double			cam_len;
	int				index;
	char			**raw;
	int				nbr_camera;
	int				nbr_light;
	int				nbr_ambient;
	int				nbr_objs;
	struct s_objs	*objs;
	struct s_cam	cam;
	struct s_objs	*light;
	struct s_objs	*ambient;
	t_pixel			cur_p;
}	t_data;

#endif