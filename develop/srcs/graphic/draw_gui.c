/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:29:41 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/23 20:29:42 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	draw_icon(t_data *d, int x, int y)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;
	int		color;

	(void) x;
	(void) y;
	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	set_color(&pixel.color, "255,0,0");
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		i++;
	}
	color = encode_rgb(pixel.color);
	return (color);
}

int	draw_gui(t_data *d)
{
	int		i;
	int		j;
	int		y;
	void	*mlx;
	void	*win;

	i = HEIGHT;
	while (i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			img_pix_put(d, j, i, draw_icon(d, j, i));
		i++;
	}

	y = 10;
	mlx = d->mlx_ptr;
	win = d->win_ptr;
	mlx_string_put(mlx, win, 35, y += 20, COLOR_TEXT, "How to Use");
	return (0);
}
