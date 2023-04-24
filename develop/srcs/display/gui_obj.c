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
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, \
	obj.icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 22, HEIGHT - 20, "Sphere");
}

void	gui_plane(t_data *d, t_objs obj, int x)
{
	// int		i;
	// int		j;

	// i = 0;
	// j = 0;
	// // paint_image(&d->pl_icon, encode_rgb(obj.color), WHITE);
	// while (i < 80)
	// {
	// 	j = 0;
	// 	while (j < 80)
	// 	{
	// 		img_pix_put(&d->menu_back, x + i, 70 + j, \
	// 		encode_rgb(obj.color));
	// 		// img_pix_put(&d->menu_back, x + i, 70 + j, \
	// 		// getpixelcolor(&d->cy_icon, i, j));
	// 		j++;
	// 	}
	// 	i++;
	// }
	// // paint_image(&d->pl_icon, WHITE, encode_rgb(obj.color));
	// // (void)obj;
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, \
	obj.icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 25, HEIGHT - 20, "Plane");
}

void	gui_cylinder(t_data *d, t_objs obj, int x)
{
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, \
	obj.icon.mlx_img, x, HEIGHT - 120);
	mlx_putstr(d, x + 17, HEIGHT - 20, "Cylinder");
}

	// int		i;
	// int		j;

	// i = 0;
	// j = 0;
	// // paint_image(&d->cy_icon, encode_rgb(obj.color), WHITE);
	// while (i < 80)
	// {
	// 	j = 0;
	// 	while (j < 80)
	// 	{
	// 		img_pix_put(&d->menu_back, x + i, 70 + j, \
	// 		getpixelcolor(&d->cy_icon, i, j));
	// 		j++;
	// 	}
	// 	i++;
	// }
	// paint_image(&d->cy_icon, WHITE, encode_rgb(obj.color));
	// (void)obj;