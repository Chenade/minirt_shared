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
	char	*prev_p;
	char	*new_p;
	// char	*pixel;
	double	r;
	double	g;
	double	b;

	// (void)amount;
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
	{
		// printf("line_len : %d, bpp : %d\n", d->img.line_len, d->img.bpp);
		prev_p = d->img.addr + (y * d->img.line_len + x * (d->img.bpp / 8));
		new_p = d->menu_back.addr + ((y - (HEIGHT - GUI_HEIGHT)) * d->menu_back.line_len + x * (d->menu_back.bpp / 8));
		// pixel = d->img.addr + (y * d->img.line_len + x * (d->img.bpp / 8));
		// printf("pix : %d\n", *(unsigned int *)pixel);
		r = ((*(unsigned int *)prev_p & 16711680) >> 16) * amount;
		g = ((*(unsigned int *)prev_p & 65280) >> 8) * amount;
		b = (*(unsigned int *)prev_p & 255) * amount;
		// printf("%d, %d, %d\n", r, g, b);
		*(unsigned int *)new_p = ((int)r << 16) + ((int)g << 8) + ((int)b);
		// (((int)(((*(unsigned int *)pixel & 16711680) >> 16) * amount) << 16) + \
		// ((int)(((*(unsigned int *)pixel & 65280) >> 8) * amount) << 8) + \
		// ((int)((*(unsigned int *)pixel & 255) * amount)));
		// printf("%f\n", (((*(unsigned int *)pixel & 16711680) >> 16) * amount));
		// *(unsigned int *)pixel = 0;
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
