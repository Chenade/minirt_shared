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

double	get_norm(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

double	cross_product(t_vector v1, t_vector v2)
{
	return ((v1.y * v2.z - v1.z * v2.y) - (v1.x * v2.z - v1.z * v2.x) \
	+ (v1.x * v2.y - v1.y * v2.x));
}

double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	normalize_vect(t_vector v)
{
	double		norm;
	t_vector	w;

	norm = get_norm(v.x, v.y, v.z);
	w.x = v.x / norm;
	w.y = v.y / norm;
	w.z = v.z / norm;
	return (w);
}

void	get_cur_vec(t_data *d, int x, int y)
{
	d->cur_p.pos.x = (-WIDTH / 2 + x);
	d->cur_p.pos.y = (HEIGHT / 2 - y);
	d->cur_p.pos.z = (d->cam.cam_len);
	d->cur_p.pos = normalize_vect(d->cur_p.pos);
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vector	vec_sum(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vector	vec_scale(t_vector v, double scaler)
{
	t_vector	w;

	w.x = v.x * scaler;
	w.y = v.y * scaler;
	w.z = v.z * scaler;
	return (w);
}
// void	set_point_param(t_data *d, )
