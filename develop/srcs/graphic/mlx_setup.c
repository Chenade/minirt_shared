/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:13:30 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:13:31 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(t_data *d)
{
	{
		d->mlx_ptr = mlx_init();
		if (!d->mlx_ptr)
			print_err("Failed init window.", d);
		d->win_ptr = mlx_new_window(d->mlx_ptr, WIDTH, HEIGHT, "fdf");
		if (!d->win_ptr)
			print_err("Failed to launch window.", d);
		d->img.mlx_img = mlx_new_image(d->mlx_ptr, WIDTH, HEIGHT);
		if (!d->img.mlx_img)
			print_err("mlx new image error", d);
		d->img.addr = mlx_get_data_addr(d->img.mlx_img, &d->img.bpp,
				&d->img.line_len, &d->img.endian);
	}
	return (0);
}

void	draw_imgs(t_data *d)
{
	int		i;
	int		j;

	ft_bzero(d->img.addr, d->img.line_len * HEIGHT);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			img_pix_put(d, j, i, ray_tracing(d, j, i));
			j++;
		}
		i++;
	}
}

int	render_frame(t_data *d)
{
	if (d->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.mlx_img, 0, 0);
	return (0);
}

int	handle_exit(t_data *d)
{
	mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	d->win_ptr = NULL;
	return (0);
}
