/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:41:00 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/28 02:41:01 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	gui_sphere(t_data *d, t_objs obj, int x)
{
	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	y = GUI_HEIGHT;
	while (i < 80)
	{
		j = 0;
		while (j < 80)
		{
			img_pix_put(d, x + i, y + j, encode_rgb(obj.color));
			j++;
		}
		i++;
	}
	mlx_putstr(d, x + 20, y + j + 20, "Sphere");
}

void	gui_plane(t_data *d, t_objs obj, int x)
{
	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	y = GUI_HEIGHT;
	while (i < 80)
	{
		j = 0;
		while (j < 80)
		{
			img_pix_put(d, x + i, y + j, encode_rgb(obj.color));
			j++;
		}
		i++;
	}
	mlx_putstr(d, x + 20, y + j + 20, "Plane");
}

void	gui_cylinder(t_data *d, t_objs obj, int x)
{
	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	y = GUI_HEIGHT;
	while (i < 80)
	{
		j = 0;
		while (j < 80)
		{
			img_pix_put(d, x + i, y + j, encode_rgb(obj.color));
			j++;
		}
		i++;
	}
	mlx_putstr(d, x + 20, y + j + 20, "Cylinder");
}
