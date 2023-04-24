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

void	print_menu_details(t_data *d)
{
	d->rec_col = 0x00505050;
	put_rect(d, vector(0,0,0), WIDTH - 1, GUI_HEIGHT - 1);
	draw_column(d, 380, 0, GUI_HEIGHT - 1);
	draw_line(d, 0, 30, WIDTH);
	d->rec_col = WHITE;
	put_rect(d, vector(390, 60, 0), 100, 120);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, \
	d->menu_back.mlx_img, 0, HEIGHT - GUI_HEIGHT);
	mlx_putstr(d, (WIDTH + 350) / 2, HEIGHT - GUI_HEIGHT + 20, "Objects");
	mlx_putstr(d, 392, HEIGHT - 140, "< - Selected + >");
}

void	print_menu_back(t_data *d)
{
	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	y = HEIGHT - GUI_HEIGHT;
	while (i < WIDTH)
	{
		j = 0;
		while (j < GUI_HEIGHT)
		{
			if (j <= 30)
				img_pix_darken(d, i, y + j, 0.2);
			else
				img_pix_darken(d, i, y + j, 0.3);
			j++;
		}
		i++;
	}
	print_menu_details(d);
}

int	draw_gui(t_data *d)
{
	int		i;
	int		x;

	i = d->index;
	x = 400;
	print_menu_back(d);
	while (i < d->nbr_objs)
	{
		((void (*)(t_data *, t_objs, int))
			(d->objs[i].gui_func))(d, d->objs[i], x);
		x += 100;
		i += 1;
	}
	i = 0;
	while (i <= d->index)
	{
		((void (*)(t_data *, t_objs, int))
			(d->objs[i].gui_func))(d, d->objs[i], x);
		x += 100;
		i += 1;
	}
	print_menu(d);
	return (0);
}
