/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:40:50 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/28 02:40:51 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	gui_camera(t_data *d, t_objs obj, int x)
{
	// int		i;
	// int		j;
	// int		y;

	// i = 0;
	// j = 0;
	// y = HEIGHT - 120;
	// while (i < 80)
	// {
	// 	j = 0;
	// 	while (j < 80)
	// 	{
	// 		img_pix_put(d, x + i, y + j, encode_rgb(obj.color));
	// 		j++;
	// 	}
	// 	i++;
	// }
	(void)obj;
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->cam_icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 20, HEIGHT - 20, "Camera");
}

void	gui_light(t_data *d, t_objs obj, int x)
{
	(void)obj;
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->light_icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 20, HEIGHT - 20, "Light");
}

void	gui_ambient(t_data *d, t_objs obj, int x)
{
	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	y = HEIGHT - 120;
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
