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

void	init_obj_imgs(t_data *d)
{
	d->sp_icon.w = 80;
	d->sp_icon.h = 80;
	d->cy_icon.w = 80;
	d->cy_icon.h = 80;
	// d->pl_icon.w = 80;
	// d->pl_icon.h = 80;
	d->sp_icon.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, \
	"./images/sp_icon.xpm", &d->sp_icon.w, &d->sp_icon.h);
	if (!d->sp_icon.mlx_img)
		print_err("mlx sphere image error", d);
	d->sp_icon.addr = mlx_get_data_addr(d->sp_icon.mlx_img, \
	&d->sp_icon.bpp, &d->sp_icon.line_len, &d->sp_icon.endian);
	d->cy_icon.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, \
	"./images/cy_icon.xpm", &d->cy_icon.w, &d->cy_icon.h);
	if (!d->cy_icon.mlx_img)
		print_err("mlx cylinder image error", d);
	d->cy_icon.addr = mlx_get_data_addr(d->cy_icon.mlx_img, \
	&d->cy_icon.bpp, &d->cy_icon.line_len, &d->cy_icon.endian);
	// d->pl_icon.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, \
	// "./images/pl_icon.xpm", &d->pl_icon.w, &d->pl_icon.h);
	// if (!d->pl_icon.mlx_img)
	// 	print_err("mlx plane image error", d);
	// d->pl_icon.addr = mlx_get_data_addr(d->pl_icon.mlx_img, \
	// &d->pl_icon.bpp, &d->pl_icon.line_len, &d->pl_icon.endian);
}

void	init_env_imgs(t_data *d)
{
	d->cam_icon.w = 80;
	d->cam_icon.h = 80;
	d->light_icon.w = 80;
	d->light_icon.h = 80;
	d->amb_icon.w = 80;
	d->amb_icon.h = 80;
	d->cam_icon.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, \
	"./images/cam_icon.xpm", &d->cam_icon.w, &d->cam_icon.h);
	if (!d->cam_icon.mlx_img)
		print_err("mlx cam image error", d);
	d->cam_icon.addr = mlx_get_data_addr(d->cam_icon.mlx_img, \
	&d->cam_icon.bpp, &d->cam_icon.line_len, &d->cam_icon.endian);
	d->light_icon.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, \
	"./images/light_icon.xpm", &d->light_icon.w, &d->light_icon.h);
	if (!d->light_icon.mlx_img)
		print_err("mlx light image error", d);
	d->light_icon.addr = mlx_get_data_addr(d->light_icon.mlx_img, \
	&d->light_icon.bpp, &d->light_icon.line_len, &d->light_icon.endian);
	d->amb_icon.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, \
	"./images/amb_icon.xpm", &d->amb_icon.w, &d->amb_icon.h);
	if (!d->amb_icon.mlx_img)
		print_err("mlx ambient image error", d);
	d->amb_icon.addr = mlx_get_data_addr(d->amb_icon.mlx_img, \
	&d->amb_icon.bpp, &d->amb_icon.line_len, &d->amb_icon.endian);
}

int	init_mlx(t_data *d)
{
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
	init_env_imgs(d);
	init_obj_imgs(d);
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
		printf("new frame\n");
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
