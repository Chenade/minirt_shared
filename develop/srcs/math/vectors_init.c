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

t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

int	init_vector(t_vector *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (0);
}

void	get_cur_vec(t_data *d, int x, int y)
{
	// double	dx;
	// double	dy;
	// double	dz;
	// double	tmp_x;
	// double	tmp_y;
	// double	tmp_z;

	// d->cur_p.dir.x = (-WIDTH / 2 + x);
	// d->cur_p.dir.y = (HEIGHT / 2 - y);
	// d->cur_p.dir.z = d->cam_len;

	// // printf("in cur vec : %f, %f, %f\n", d->cam->angle_x, \
	// // d->cam->angle_y, d->cam->angle_z);

	// // First, rotate around the Y-axis
	// dx = d->cur_p.dir.x * cos(d->cam->angle_y) + d->cur_p.dir.z * sin(d->cam->angle_y);
	// dy = d->cur_p.dir.y;
	// dz = -d->cur_p.dir.x * sin(d->cam->angle_y) + d->cur_p.dir.z * cos(d->cam->angle_y);

	// // Next, rotate around the X-axis
	// tmp_x = dx;
	// tmp_y = dy * cos(d->cam->angle_x) - dz * sin(d->cam->angle_x);
	// tmp_z = dy * sin(d->cam->angle_x) + dz * cos(d->cam->angle_x);

	// // Finally, rotate around the Z-axis
	// d->cur_p.dir.x = tmp_x * cos(d->cam->angle_z) - tmp_y * sin(d->cam->angle_z);
	// d->cur_p.dir.y = tmp_x * sin(d->cam->angle_z) + tmp_y * cos(d->cam->angle_z);
	// d->cur_p.dir.z = tmp_z;

	// Potential new method :
	d->cur_p.dir = vec_sum(vec_scale(d->cam->dir, d->cam_len), \
	vec_sum(vec_scale(d->cam->dir_x, (-WIDTH / 2 + x)), \
	vec_scale(d->cam->dir_y, (HEIGHT / 2 - y))));

	// printf("new dir  [d->cur_p.dir.x] =%f [d->cur_p.dir.y] = %f [d->cur_p.dir.z] = %f\n", d->cur_p.dir.x, d->cur_p.dir.y, d->cur_p.dir.z);
}
