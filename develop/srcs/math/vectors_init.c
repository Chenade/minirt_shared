/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:22:40 by znogueir          #+#    #+#             */
/*   Updated: 2023/03/26 22:22:41 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_vector(t_vector *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (0);
}

void	get_cur_vec(t_data *d, int x, int y)
{
	double	dx;
	double	dy;
	double	dz;
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	d->cur_p.dir.x = (-WIDTH / 2 + x);
	d->cur_p.dir.y = (HEIGHT / 2 - y);
	d->cur_p.dir.z = d->cam_len;
	// d->cur_p.dir = normalize_vect(vec_sum(d->cur_p.dir, normalize_vect(d->cam->dir)));
	dx = d->cur_p.dir.x * cos(d->cam->angle_z) - \
	d->cur_p.dir.y * sin(d->cam->angle_z);
	dy = d->cur_p.dir.x * sin(d->cam->angle_z) + \
	d->cur_p.dir.y * cos(d->cam->angle_z);
	dz = d->cur_p.dir.z;
	tmp_z = dz * cos(d->cam->angle_y) - dx * sin(d->cam->angle_y);
	tmp_x = dz * sin(d->cam->angle_y) + dx * cos(d->cam->angle_y);
	tmp_y = dy;
	d->cur_p.dir.y = tmp_y * cos(d->cam->angle_x) - \
	tmp_z * sin(d->cam->angle_x);
	d->cur_p.dir.z = tmp_y * sin(d->cam->angle_x) + \
	tmp_z * cos(d->cam->angle_x);
	d->cur_p.dir.x = tmp_x;
	d->cur_p.dir = normalize_vect(d->cur_p.dir);
}
