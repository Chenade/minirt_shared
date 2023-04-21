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

void	print_vec(t_vector v)
{
	printf("x : %f, y : %f, z : %f\n", v.x, v.y, v.z);
}

int	compare_vecs(t_vector v, t_vector w)
{
	if (v.x != w.x)
		return (0);
	if (v.y != w.y)
		return (0);
	return (v.z == w.z);
}

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
	d->cur_p.dir = vec_sum(vec_scale(d->cam->dir_x, (-WIDTH / 2 + x)), \
	vec_sum(vec_scale(d->cam->dir, d->cam_len), \
	vec_scale(d->cam->dir_y, (HEIGHT / 2 - y))));
}
