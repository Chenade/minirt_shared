/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:13:13 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:13:14 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_matrix_rotate(t_data *d, int i)
{
	t_vector	tmp;

	init_vector(&tmp, d->map_3d[i]->x, d->map_3d[i]->y, d->map_3d[i]->z);
	d->map_3d[i]->x = d->map_3d[i]->x;
	d->map_3d[i]->y = tmp.y * cos(d->rot->x) + tmp.z * sin(d->rot->x);
	d->map_3d[i]->z = tmp.y * sin(d->rot->x) * -1 + tmp.z * cos(d->rot->x);
	init_vector(&tmp, d->map_3d[i]->x, d->map_3d[i]->y, d->map_3d[i]->z);
	d->map_3d[i]->x = tmp.x * cos(d->rot->y) + tmp.z * sin(d->rot->y);
	d->map_3d[i]->y = tmp.y;
	d->map_3d[i]->z = tmp.x * sin(d->rot->y) * -1 + tmp.z * cos(d->rot->y);
	init_vector(&tmp, d->map_3d[i]->x, d->map_3d[i]->y, d->map_3d[i]->z);
	d->map_3d[i]->x = tmp.x * cos(d->rot->z) - tmp.y * sin(d->rot->z);
	d->map_3d[i]->y = tmp.x * cos(d->rot->z) + tmp.y * sin(d->rot->z);
	d->map_3d[i]->z = tmp.z;
	return (0);
}

int	ft_matrix_to_vector(t_data *d, int i)
{
	t_vector	*_2d;
	t_vector	*_3d;

	_2d = d->map_2d[i];
	_3d = d->map_3d[i];
	_2d->x = (_3d->x * d->u->x + _3d->y * d->u->y + _3d->z * d->u->z);
	_2d->y = (_3d->x * d->v->x + _3d->y * d->v->y + _3d->z * d->v->z);
	_2d->c = (_3d->c);
	return (0);
}

int	ft_matrix_iter(t_data *d)
{
	int			x;
	int			y;
	int			i;

	y = -1;
	while (++y < d->map_h)
	{
		x = -1;
		while (++x < d->map_w)
		{
			i = xy_to_x(d, x, y);
			ft_matrix_rotate(d, i);
			ft_matrix_to_vector(d, i);
		}
	}
	return (0);
}

int	ft_matrix_move(t_data *d, t_vector min, t_vector max)
{
	int	x;
	int	y;
	int	size;

	y = -1;
	while (++y < d->map_h)
	{
		x = -1;
		while (++x < d->map_w)
		{
			size = (max.x - min.x) / 2;
			d->map_2d[xy_to_x(d, x, y)]->x
				+= ft_abs(min.x) + WIDTH / 2 - size + d->center->x;
			size = (max.y - min.y) / 2;
			d->map_2d[xy_to_x(d, x, y)]->y
				+= ft_abs(min.y) + HEIGHT / 2 - size - d->center->y;
		}
	}
	return (0);
}

int	ft_matrix_center(t_data *d)
{
	int			x;
	int			y;
	t_vector	min;
	t_vector	max;

	min.x = d->map_2d[0]->x;
	min.y = d->map_2d[0]->y;
	max.x = d->map_2d[0]->x;
	max.y = d->map_2d[0]->y;
	y = -1;
	while (++y < d->map_h)
	{
		x = -1;
		while (++x < d->map_w)
		{
			min.x = ft_min(min.x, d->map_2d[xy_to_x(d, x, y)]->x);
			min.y = ft_min(min.y, d->map_2d[xy_to_x(d, x, y)]->y);
			max.x = ft_max(max.x, d->map_2d[xy_to_x(d, x, y)]->x);
			max.y = ft_max(max.y, d->map_2d[xy_to_x(d, x, y)]->y);
		}
	}
	ft_matrix_move(d, min, max);
	return (0);
}
