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

void	mlx_putstr(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, COLOR_WHITE, str);
}

void	mlx_putstr_b(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, 0x00000000, str);
}


void	print_menu(t_data *d)
{
	int		y;

	y = HEIGHT - 180;
	// mlx_putstr_b(d, 44, y + 20, "< How to Use >");
	// mlx_putstr_b(d, 46, y + 20, "< How to Use >");
	// mlx_putstr_b(d, 45, y + 21, "< How to Use >");
	// mlx_putstr_b(d, 45, y + 19, "< How to Use >");
	mlx_putstr(d, 45, y += 20, "< How to Use >");
	mlx_putstr(d, 35, y += 20, "Arrow Keys: Move X/Y");
	mlx_putstr(d, 35, y += 20, "Key Z/X: Move Z");
	mlx_putstr(d, 35, y += 20, "Key Q/A: Rotate X");
	mlx_putstr(d, 35, y += 20, "Key W/S: Rotate Y");
	mlx_putstr(d, 35, y += 20, "Key E/D: Rotate Z");
	mlx_putstr(d, 35, y += 20, "Key U/I: Height");
	mlx_putstr(d, 35, y += 20, "Key J/K: radius");
}

void	draw_line(t_data *d, int x, int y, int l)
{
	int	i;

	i = -1;
	while (i++ < l)
		img_pix_put(d, x + i, y, d->cur_col);
}

void	draw_column(t_data *d, int x, int y, int l)
{
	int	i;

	i = -1;
	while (i++ < l)
		img_pix_put(d, x, y + i, d->cur_col);
}

void	put_rect(t_data *d, int x, int y, int w, int h, int color)
{
	d->cur_col = color;
	draw_line(d, x, y, w);
	draw_column(d, x, y, h);
	draw_line(d, x, y + h, w);
	draw_column(d, x + w, y, h);
}

void	print_menu_outline(t_data *d)
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
		while (j < 30)
		{
			img_pix_put(d, i, y + j, 0x00080808);
			j++;
		}
		i++;
	}
	put_rect(d, 0, HEIGHT - GUI_HEIGHT, WIDTH - 1, GUI_HEIGHT - 1, 0x00404040);
	draw_column(d, 380, HEIGHT - GUI_HEIGHT, GUI_HEIGHT);
	draw_line(d, 0, HEIGHT - GUI_HEIGHT + 30, WIDTH);
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
			img_pix_put(d, i, y + j, 0x00202020);
			j++;
		}
		i++;
	}
	print_menu_outline(d);
	mlx_putstr(d, (WIDTH + 350) / 2, HEIGHT - GUI_HEIGHT + 20, "Objects");
}

int	draw_gui(t_data *d)
{
	int		i;
	int		x;

	i = d->index;
	x = 400;
	print_menu_back(d);
	// mlx_putstr(d, x + 2, HEIGHT - 165, "Press Tab -->");
	mlx_putstr(d, x + 5, HEIGHT - 140, "> Selected <");
	mlx_putstr(d, x + 273, HEIGHT - 138, "-  -  -  -  -  -  -  - Press Tab -  -  -  -  -  -  -  ->");
	put_rect(d, x - 10, HEIGHT - 130, 100, 120, 0x00FFFFFF);
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
