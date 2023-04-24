/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:12:29 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:12:32 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

void	img_pix_darken(t_data *d, int x, int y, double amount)
{
	int		r;
	int		g;
	int		b;
	char	*prev_p;
	char	*new_p;

	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
	{
		prev_p = d->img.addr + (y * d->img.line_len + x * (d->img.bpp / 8));
		new_p = d->menu_back.addr + ((y - (HEIGHT - GUI_HEIGHT)) \
		* d->menu_back.line_len + x * (d->menu_back.bpp / 8));
		r = ((*(unsigned int *)prev_p & 16711680) >> 16) * amount;
		g = ((*(unsigned int *)prev_p & 65280) >> 8) * amount;
		b = (*(unsigned int *)prev_p & 255) * amount;
		*(unsigned int *)new_p = (r << 16) + (g << 8) + (b);
	}
}

int	getpixelcolor(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->addr + x * (img->bpp / 8) + y
		* img->line_len));
}

int	encode_rgb(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}
