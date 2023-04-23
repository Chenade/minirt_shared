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

void	mlx_putstr_r(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, RED, str);
}

void	mlx_putstr_g(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, GREEN, str);
}

void	mlx_putstr_b(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, BLUE, str);
}

void	print_move_menu(t_data *d, char *type)
{
	int		y;

	y = HEIGHT - GUI_HEIGHT + 40;
	mlx_putstr(d, 178, HEIGHT - GUI_HEIGHT + 20, type);
	mlx_putstr(d, 20, y + 20, "Move :");
	mlx_putstr(d, 64, y += 20, "Along   (Right/Left) : Left / Right Arrows");
	mlx_putstr_r(d, 100, y, "X");
	mlx_putstr(d, 64, y += 20, "Along   (Up/Down) : Y / H");
	mlx_putstr_g(d, 100, y, "Y");
	mlx_putstr(d, 64, y += 20, "Along   (Forwards/Backwards) : Up / Down Arrows");
	mlx_putstr_b(d, 100, y, "Z");
}

void	print_complete_menu(t_data *d, char *type)
{
	int		y;

	y = HEIGHT - GUI_HEIGHT + 110;
	print_move_menu(d, type);
	mlx_putstr(d, 20, y + 20, "Rotate :");
	mlx_putstr(d, 74, y += 20, "Around   : W / S");
	mlx_putstr_r(d, 117, y, "X");
	mlx_putstr(d, 74, y += 20, "Around   : D / A");
	mlx_putstr_g(d, 117, y, "Y");
	mlx_putstr(d, 74, y += 20, "Around   : E / Q");
	mlx_putstr_b(d, 117, y, "Z");
}

void	print_cam_menu(t_data *d)
{
	int		y;

	y = HEIGHT - GUI_HEIGHT + 50;
	mlx_putstr(d, 175, HEIGHT - GUI_HEIGHT + 20, "Camera");
	mlx_putstr(d, 35, y += 20, "Look Around : W A S D");
	mlx_putstr(d, 35, y += 20, "Tilt right and left : E / Q");
	mlx_putstr(d, 35, y += 40, "Move Around : Arrow keys");
	mlx_putstr(d, 35, y += 20, "Go Up and Down : Y / H");
}

void	print_menu(t_data *d)
{
	int	type;

	type = d->objs[d->index].type;
	if (type == CAM)
		print_cam_menu(d);
	else if (type == LIGHT)
		print_move_menu(d, "Light");
	else if (type == AMB)
		mlx_putstr(d, 160, HEIGHT - GUI_HEIGHT + 20, "Ambient light");
	else if (type == SP)
		print_move_menu(d, "Sphere");
	else if (type == PL)
		print_complete_menu(d, "Plane");
	else if (type == CY)
		print_complete_menu(d, "Cylinder");
	else if (type == CO)
		print_complete_menu(d, "Cone");
}

void	draw_line(t_data *d, int x, int y, int l)
{
	int	i;

	i = -1;
	while (i++ < l)
		img_pix_put(&d->menu_back, x + i, y, d->cur_col);
}

void	draw_column(t_data *d, int x, int y, int l)
{
	int	i;

	i = -1;
	while (i++ < l)
		img_pix_put(&d->menu_back, x, y + i, d->cur_col);
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
			img_pix_put(&d->img, i, y + j, 0x00080808);
			j++;
		}
		i++;
	}
	put_rect(d, 0, 0, WIDTH - 1, GUI_HEIGHT - 1, 0x00404040);
	draw_column(d, 380, 0, GUI_HEIGHT - 1);
	draw_line(d, 0, 30, WIDTH);
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
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->menu_back.mlx_img, 0, HEIGHT - GUI_HEIGHT);
	mlx_putstr(d, (WIDTH + 350) / 2, HEIGHT - GUI_HEIGHT + 20, "Objects");
	put_rect(d, 0, 0, WIDTH - 1, GUI_HEIGHT - 1, 0x00505050);
	draw_column(d, 380, 0, GUI_HEIGHT - 1);
	draw_line(d, 0, 30, WIDTH);
}

int	draw_gui(t_data *d)
{
	int		i;
	int		x;

	i = d->index;
	x = 400;
	print_menu_back(d);
	mlx_putstr(d, x - 8, HEIGHT - 140, "< - Selected + >");
	put_rect(d, x - 10, 60, 100, 120, 0x00FFFFFF);
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
	// print_menu_outline(d);
	return (0);
}
