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
	t_vector	pos;
	t_color		color;
}	t_pixel;

typedef struct s_data	t_data;
typedef struct s_objs	t_objs;

typedef struct s_objs
{
	void		*collision_func;
	t_vector	cord;
	t_vector	orientation;
	t_color		color;
	double		fov;
	double		ratio;
	double		diameter;
	double		height;
}	t_objs;

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
	void				*win_ptr;
	void				*mlx_ptr;
	t_img				img;

	char				**raw;
	int					nbr_camera;
	int					nbr_light;
	int					nbr_ambient;
	int					nbr_objs;
	struct s_objs		*objs;
}	t_data;

#endif