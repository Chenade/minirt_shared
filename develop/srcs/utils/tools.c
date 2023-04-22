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

void	img_pix_put(t_data *d, int x, int y, int color)
{
	char	*pixel;

	if (y >= 0 && y < WIN_HEIGHT && x >= 0 && x < WIDTH)
	{
		pixel = d->img.addr + (y * d->img.line_len + x * (d->img.bpp / 8));
		*(unsigned int *)pixel = color;
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
