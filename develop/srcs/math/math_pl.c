/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:49:57 by znogueir          #+#    #+#             */
/*   Updated: 2023/03/26 01:49:59 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
n(a, b, c);

t = (-a * (px - x0) - b * (py - y0) - c * (pz - z0)) /
	(a * vx + b * vy + c * vz);

check that (a * vx + b * vy + c * vz) != 0;
*/

/*
	double		norm;
	t_vector	v;

	norm = get_norm(-WIDTH / 2 + x, HEIGHT / 2 - y, d->cam_len);
	v.x = (-WIDTH / 2 + x) / norm;
	v.y = (HEIGHT / 2 - y) / norm;
	v.z = (d->cam_len) / norm;

	we should calculate v only once for each pixel and then send it to each
	collision function of each object;
	need a "current pixel vector" thing in data;
	also need the cam info in data or smth;
*/

double	check_vn2(t_objs *obj, t_data *d)
{
	double		vn;
	t_vector	v;

	v = d->cur_p.dir;
	vn = (obj->dir.x * v.x + obj->dir.y * v.y + \
		obj->dir.z * v.z);
	return (vn);
}

double	calculate_scaler_pl2(t_objs *obj, t_data *d, t_vector p)
{
	double		t;
	t_vector	v;

	v = d->cur_p.dir;
	t = (-obj->dir.x * (p.x - obj->pos.x) \
		- obj->dir.y * (p.y - obj->pos.y) \
		- obj->dir.z * (p.z - obj->pos.z)) / \
		(obj->dir.x * v.x + obj->dir.y * v.y + \
		obj->dir.z * v.z);
	return (t);
}

/*
t : scaler, a : origin point of the plane, p0 : origin point of camera,
v : direction vector of the current pixel, n : vector normal to the plane;

t = (a - p0).n / v.n;

special case : v.n = 0 -> v is parallel to the plane, so it's either never
intersecting, or intersecting to infinity if the line is part of the plane;
(we dont consider this to be an intersection)

special case #2 : t < 0 -> the intersection between v and the plane is behind
us which means we dont see it; (we only consider solutions >= 0);
*/

// ------------------------------------------------------------------------

// double	check_vn(t_objs *obj, t_data *d, double x, double y)
// {
// 	double		norm;
// 	t_vector	v;

// 	norm = get_norm(-WIDTH / 2 + x, HEIGHT / 2 - y, d->cam_len);
// 	v.x = (-WIDTH / 2 + x) / norm;
// 	v.y = (HEIGHT / 2 - y) / norm;
// 	v.z = (d->cam_len) / norm;
// 	return (cross_product(v, obj->dir));
// }
