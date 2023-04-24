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

char	*get_icon_name(int type)
{
	if (type == CAM)
		return ("./images/cam_icon.xpm");
	if (type == AMB)
		return ("./images/amb_icon.xpm");
	if (type == LIGHT)
		return ("./images/light_icon.xpm");
	if (type == SP)
		return ("./images/sp_icon.xpm");
	// if (type == PL)
	// 	return ("./images/pl_icon.xpm");
	return ("./images/cy_icon.xpm");
	// if (type == CO)
	// 	return ("./images/co_icon.xpm");
}

void	init_icons(t_data *d)
{
	int		i;
	char	*img_name;

	i = 0;
	while (i < d->nbr_objs)
	{
		d->objs[i].icon.w = 80;
		d->objs[i].icon.h = 80;
		if (d->objs[i].type != PL) // for now !!
		{
			img_name = get_icon_name(d->objs[i].type);
			d->objs[i].icon.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, \
			img_name, &d->objs[i].icon.w, &d->objs[i].icon.h);
			if (!d->objs[i].icon.mlx_img)
				print_err("mlx_img icon error", d);
			d->objs[i].icon.addr = \
			mlx_get_data_addr(d->objs[i].icon.mlx_img, &d->objs[i].icon.bpp, \
			&d->objs[i].icon.line_len, &d->objs[i].icon.endian);
			if (d->objs[i].type != CAM)
				paint_image(&d->objs[i].icon, encode_rgb(d->objs[i].color), \
				WHITE);
		}
		i++;
	}
}

int	init_mlx(t_data *d)
{
	printf("nbr objs : %d\n", d->nbr_objs);
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
		print_err("Failed init window.", d);
	d->win_ptr = mlx_new_window(d->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!d->win_ptr)
		print_err("Failed to launch window.", d);
	d->img.mlx_img = mlx_new_image(d->mlx_ptr, WIDTH, HEIGHT);
	if (!d->img.mlx_img)
		print_err("mlx new image error", d);
	d->img.addr = mlx_get_data_addr(d->img.mlx_img, &d->img.bpp,
			&d->img.line_len, &d->img.endian);
	d->menu_back.mlx_img = mlx_new_image(d->mlx_ptr, WIDTH, GUI_HEIGHT);
	if (!d->menu_back.mlx_img)
		print_err("mlx new image error", d);
	d->menu_back.addr = mlx_get_data_addr(d->menu_back.mlx_img, \
	&d->menu_back.bpp, &d->menu_back.line_len, &d->menu_back.endian);
	init_icons(d);
	return (0);
}

void	draw_imgs(t_data *d)
{
	int		i;
	int		j;

	// ft_bzero(d->img.addr, d->img.line_len * WIN_HEIGHT);
	i = 0;
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			img_pix_put(&d->img, j, i, ray_tracing(d, j, i));
		i++;
	}
	d->img_changed = 1;
}

int	render_frame(t_data *d)
{
	if (d->win_ptr == NULL)
		return (1);
	if (d->img_changed == 1)
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.mlx_img, 0, 0);
		if (d->display_gui == 1)
			draw_gui(d);
		d->img_changed = 0;
	}
	return (0);
}

int	handle_exit(t_data *d)
{
	mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	d->win_ptr = NULL;
	return (0);
}

int	handle_plus_minus(int keysym, t_data *d)
{
	if ((keysym == XK_equal || keysym == XK_minus) && d->display_gui == 1)
	{
		if (keysym == XK_equal)
			d->index = (d->index + 1) % (d->nbr_objs);
		else
			d->index--;
		if (d->index < 0)
			d->index = d->nbr_objs - 1;
		return (1);
	}
	return (0);
}

int	handle_keypress(int keysym, t_data *d)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(d->mlx_ptr, d->win_ptr);
		d->win_ptr = NULL;
	}
	else if (handle_plus_minus(keysym, d))
	{
		d->img_changed = 1;
		draw_gui(d);
	}
	else if (keysym == XK_p)
		key_saved(d);
	else if (keysym == XK_m)
	{
		d->display_gui = (d->display_gui == 0);
		d->img_changed = 1;
	}
	else if (((int (*)(t_data *, int)) \
	(d->objs[d->index].keyboard_func))(d, keysym))
		draw_imgs(d);
	return (0);
}
