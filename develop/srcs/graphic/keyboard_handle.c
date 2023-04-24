/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:35:47 by ykuo              #+#    #+#             */
/*   Updated: 2023/04/24 20:35:48 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
