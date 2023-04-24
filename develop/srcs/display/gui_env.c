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

void	paint_image(t_img *img, int color, int target)
{
	char	*pixel;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 80)
	{
		j = 0;
		while (j < 80)
		{
			pixel = img->addr + (j * img->line_len + i * (img->bpp / 8));
			if (*(unsigned int *)pixel == (unsigned int)target)
				*(unsigned int *)pixel = color;
			j++;
		}
		i++;
	}
}

void	gui_camera(t_data *d, t_objs obj, int x)
{
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, \
	obj.icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 22, HEIGHT - 20, "Camera");
}

void	gui_light(t_data *d, t_objs obj, int x)
{
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, \
	obj.icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 25, HEIGHT - 20, "Light");
}

void	gui_ambient(t_data *d, t_objs obj, int x)
{
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, \
	obj.icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 2, HEIGHT - 20, "Ambient Light");
}
