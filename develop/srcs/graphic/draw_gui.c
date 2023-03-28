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

void	print_menu(t_data *d)
{
	int		y;

	y = HEIGHT + 10;
	mlx_putstr(d, 45, y += 20, "< How to Use >");
	mlx_putstr(d, 35, y += 20, "Arrow Keys: Move X/Y");
	mlx_putstr(d, 35, y += 20, "Key Z/X: Move Z");
	mlx_putstr(d, 35, y += 20, "Key Q/A: Rotate X");
	mlx_putstr(d, 35, y += 20, "Key W/S: Rotate Y");
	mlx_putstr(d, 35, y += 20, "Key E/D: Rotate Z");
	mlx_putstr(d, 35, y += 20, "Key U/I: Height");
	mlx_putstr(d, 35, y += 20, "Key J/K: Diameter");
}

int	draw_gui(t_data *d)
{
	int		i;
	int		x;

	i = d->index;
	x = 200;
	mlx_putstr(d, 215, HEIGHT + 30, "Selected");
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
