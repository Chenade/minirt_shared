/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:13:03 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:13:06 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_sphere(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	if (((keysym == XK_j || keysym == XK_k) && d->objs[d->index].is_hidden == 0) \
	|| keysym == XK_n)
		i = 1;
	if (keysym == XK_n)
		d->objs[d->index].is_hidden = (d->objs[d->index].is_hidden == 0);
	if (keysym == XK_j && d->objs[d->index].is_hidden == 0)
		d->objs[d->index].radius += STEP;
	else if (keysym == XK_k && d->objs[d->index].is_hidden == 0)
	{
		if (d->objs[d->index].radius > STEP)
			d->objs[d->index].radius -= STEP;
	}
	d->objs[d->index].math.radius_2 = \
	d->objs[d->index].radius * d->objs[d->index].radius;
	return (i);
}

int	key_plane(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	i = (i || ft_dir(d, &d->objs[d->index], keysym));
	if (keysym == XK_n)
		i = 1;
	if (keysym == XK_n)
		d->objs[d->index].is_hidden = (d->objs[d->index].is_hidden == 0);
	return (i);
}

int	key_cylinder(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	i = (i || ft_dir(d, &d->objs[d->index], keysym));
	if (((keysym == XK_j || keysym == XK_k || keysym == XK_u || \
	keysym == XK_i) && d->objs[d->index].is_hidden == 0) || keysym == XK_n)
		i = 1;
	if (keysym == XK_n)
		d->objs[d->index].is_hidden = (d->objs[d->index].is_hidden == 0);
	if (keysym == XK_j && d->objs[d->index].is_hidden == 0)
		d->objs[d->index].radius += STEP;
	else if (keysym == XK_k && d->objs[d->index].radius > STEP && \
	d->objs[d->index].is_hidden == 0)
		d->objs[d->index].radius -= STEP;
	if (keysym == XK_u && d->objs[d->index].is_hidden == 0)
		d->objs[d->index].height += STEP;
	else if (keysym == XK_i && d->objs[d->index].is_hidden == 0)
	{
		if (d->objs[d->index].height > STEP)
			d->objs[d->index].height -= STEP;
	}
	init_cyl(d, d->index);
	return (i);
}

int	key_cone(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	i = (i || ft_dir(d, &d->objs[d->index], keysym));
	if (((keysym == XK_j || keysym == XK_k || keysym == XK_u || \
	keysym == XK_i) && d->objs[d->index].is_hidden == 0) || keysym == XK_n)
		i = 1;
	if (keysym == XK_n)
		d->objs[d->index].is_hidden = (d->objs[d->index].is_hidden == 0);
	if (keysym == XK_j && d->objs[d->index].is_hidden == 0)
		d->objs[d->index].radius += STEP;
	else if (keysym == XK_k && d->objs[d->index].is_hidden == 0)
	{
		if (d->objs[d->index].radius > STEP)
			d->objs[d->index].radius -= STEP;
	}
	if (keysym == XK_u && d->objs[d->index].is_hidden == 0)
		d->objs[d->index].height += STEP;
	else if (keysym == XK_i && d->objs[d->index].is_hidden == 0)
	{
		if (d->objs[d->index].height > STEP)
			d->objs[d->index].height -= STEP;
	}
	init_cone(d, d->index);
	return (i);
}
