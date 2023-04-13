/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:50:19 by ykuo              #+#    #+#             */
/*   Updated: 2023/04/13 14:50:20 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	gui_camera(t_data *d, t_objs obj, int x)
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
	mlx_putstr(d, x + 20, y + j + 20, "Camera");
}

void	gui_light(t_data *d, t_objs obj, int x)
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
	mlx_putstr(d, x + 20, y + j + 20, "Light");
}

void	gui_ambient(t_data *d, t_objs obj, int x)
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
	mlx_putstr(d, x + 20, y + j + 20, "Ambient");
}
