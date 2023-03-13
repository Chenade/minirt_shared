/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:16 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:12:18 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_linear(t_data *d, t_vector delta, int pos)
{
	(void) d;
	(void) delta;
	(void) pos;
	if (ft_atoi(d->map[pos]) == 0)
		return (COLOR_WHITE);
	return (8396832);
}

t_vector	ft_draw_sign(t_vector f, t_vector s)
{
	t_vector	sign;

	if (f.x < s.x)
		sign.x = 1;
	else
		sign.x = -1;
	if (f.y < s.y)
		sign.y = 1;
	else
		sign.y = -1;
	return (sign);
}

void	ft_lines_draw(t_data *d, t_vector f, t_vector s)
{
	t_vector	delta;
	t_vector	sign;
	t_vector	cur;
	int			error[2];

	delta.x = ft_abs(s.x - f.x);
	delta.y = ft_abs(s.y - f.y);
	sign = ft_draw_sign(f, s);
	error[0] = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		img_pix_put(d, cur.x, cur.y, cur.c);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

int	draw_gui(t_data *d)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 200;
	mlx = d->mlx_ptr;
	win = d->win_ptr;
	mlx_string_put(mlx, win, 65, y += 20, COLOR_TEXT, "How to Use");
	mlx_string_put(mlx, win, 15, y += 35, COLOR_TEXT, "Zoom: | J | / | K |");
	mlx_string_put(mlx, win, 15, y += 30, COLOR_TEXT, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, COLOR_TEXT, "Height: | R | / | F |");
	mlx_string_put(mlx, win, 15, y += 30, COLOR_TEXT, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 30, COLOR_TEXT, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, COLOR_TEXT, "X-Axis - | Q | / | A |");
	mlx_string_put(mlx, win, 57, y += 25, COLOR_TEXT, "Y-Axis - | W | / | S |");
	mlx_string_put(mlx, win, 57, y += 25, COLOR_TEXT, "Z-Axis - | E | / | D |");
	mlx_string_put(mlx, win, 15, y += 30, COLOR_TEXT, "Projection Change");
	mlx_string_put(mlx, win, 57, y += 25, COLOR_TEXT, "P Key");
	return (0);
}

void	draw_maps(t_data *d)
{
	int			x;
	int			y;
	t_vector	cur;

	ft_matrix_iter(d);
	ft_matrix_center(d);
	y = -1;
	while (++y < d->map_h)
	{
		x = -1;
		while (++x < d->map_w)
		{
			cur = *(d->map_2d[xy_to_x(d, x, y)]);
			if (x + 1 != d->map_w)
				ft_lines_draw(d, cur, *(d->map_2d[xy_to_x(d, x + 1, y)]));
			if (y + 1 != d->map_h)
				ft_lines_draw(d, cur, *(d->map_2d[xy_to_x(d, x, y + 1)]));
		}
	}
}
