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

	i = ft_move(&d->objs[d->index], keysym);
	if (keysym == XK_j || keysym == XK_k)
		i = 1;
	if (keysym == XK_j)
		d->objs[d->index].radius += STEP;
	else if (keysym == XK_k)
	{
		if (d->objs[d->index].radius > STEP)
			d->objs[d->index].radius -= STEP;
	}
	return (i);
}

int	key_plane(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = (i || ft_dir(&d->objs[d->index], keysym));
	return (i);
}

int	key_cylinder(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = ft_dir(&d->objs[d->index], keysym);
	if (keysym == XK_j || keysym == XK_k || keysym == XK_u || keysym == XK_i)
		i = 1;
	if (keysym == XK_j)
		d->objs[d->index].radius += STEP;
	else if (keysym == XK_k)
	{
		if (d->objs[d->index].radius > STEP)
			d->objs[d->index].radius -= STEP;
	}
	if (keysym == XK_u)
		d->objs[d->index].height += STEP;
	else if (keysym == XK_i)
	{
		if (d->objs[d->index].height > STEP)
			d->objs[d->index].height -= STEP;
	}
	d->objs[d->index].dir = \
	normalize_vect(d->objs[d->index].dir);
	return (i);
}
