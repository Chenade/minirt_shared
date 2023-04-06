/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:16:14 by znogueir          #+#    #+#             */
/*   Updated: 2023/03/29 17:16:16 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
cylinder equations :

first, interaction with an infinite tube:

at^2 + bt + c = 0 (like the spheres);

a = va.va     -> va = (s x v x s);      ->  *

b = 2ra.va;   -> ra = s x (r0 - rt) x s;

c = ra.ra - R^2;

v = direction vector of the ray;
r0 = cord of the point of emission (cam->cord);
rt = cord of obj;
s = direction vector of the tube;
R = radius of tube;

* : "x" means cross product. see vectors functions;

--------------------------------------------------

now we limit the tube.

we have to check for 2 conditions :

(hit_p - ra1).s > 0         &&         (hit_p - ra2).s < 0

hit_p = r0 + v*t (so the position of the point of intersection between
		the ray and the tube at t time in the v direction starting at r0,
		r0 being 'p' in my functions);

ra1 & ra2 = positions of the 2 extremities of the central axis
			relative to the starting point of the ray (r0 or 'p');

s = same as above, direction vector of the tube;

--------------------------------------------------

and finally, we check for the planes at each end of the tube;

pos of pl_1 : pos of the cyl + direction vector(normalized) * height / 2;
pos of pl_2 : pos of the cyl + direction vector(normalized) * -height / 2;

direction of pl_1 : direction vector of cyl (normalized);
direction of pl_2 : -direction vector of cyl (normalized);

we check for intersections on both those planes, and if they
are inside the diameter of the cylinder;
*/

t_vector	calculate_cyl_normal(t_objs *cyl, t_vector hit_pt)
{
	double		t;
	t_vector	pt;
	t_vector	cyl_bottom;

	cyl_bottom = vec_sum(cyl->cord, vec_scale(cyl->orientation, \
	cyl->height / 2));
	t = dot_product(vec_sub(hit_pt, cyl_bottom), cyl->orientation);
	pt = vec_sum(cyl_bottom, vec_scale(cyl->orientation, t));
	return (normalize_vect(vec_sub(hit_pt, pt)));
}

// double	calculate_scaler_pl2(t_objs *obj, t_data *d, t_vector p)
// {
// 	double		t;
// 	t_vector	v;

// 	v = d->cur_p.pos;
// 	t = (-obj->orientation.x * (p.x - obj->cord.x) \
// 		- obj->orientation.y * (p.y - obj->cord.y) \
// 		- obj->orientation.z * (p.z - obj->cord.z)) / \
// 		(obj->orientation.x * v.x + obj->orientation.y * v.y + \
// 		obj->orientation.z * v.z);
// 	return (t);
// }

double	hit_cap(t_vector dir, t_data *d, t_vector p, t_vector center, double radius)
{
	double		t;
	t_vector	v;

	// (void)radius;
	v = d->cur_p.pos;
	t = (-dir.x * (p.x - center.x) \
		- dir.y * (p.y - center.y) \
		- dir.z * (p.z - center.z)) / \
		(dir.x * v.x + dir.y * v.y + \
		dir.z * v.z);
	//hit_point = p + t*v; vec_sum(p, vec_scaler(v, t));
	//dist between hit_point and center <= radius;
	// printf("norm : %f\n", get_vec_norm(vec_sub(vec_sum(p, vec_scale(v, t)), center)));
	// printf("test : %f, %f, %f\n", \
	// vec_sub(vec_sum(p, vec_scale(v, t)), center).x, \
	// vec_sub(vec_sum(p, vec_scale(v, t)), center).y, \
	// vec_sub(vec_sum(p, vec_scale(v, t)), center).z);
	if (t > 0 && \
	fabs(get_vec_norm(vec_sub(center, vec_sum(p, vec_scale(v, t))))) < radius)
		return (t);
	return (-1);
}

double	calculate_scaler_caps(t_objs *cyl, t_data *d, t_vector p)
{
	double	t1;
	double	t2;
	double	res;

	t1 = hit_cap(cyl->orientation, d, p, \
		vec_sum(cyl->cord, vec_scale(cyl->orientation, cyl->height / 2)), cyl->diameter / 2);
	t2 = hit_cap(vec_scale(cyl->orientation, -1), d, p, \
		vec_sum(cyl->cord, vec_scale(cyl->orientation, -cyl->height / 2)), cyl->diameter / 2);
	res = smallest_positive(t1, t2);
	if (res == t1)
		cyl->normal = cyl->orientation;
	else
		cyl->normal = vec_scale(cyl->orientation, -1);
	return (res);
	// for each plane, check for collisions;
	// then check if the distance between the cord of plane (center
	// of the cap) and the hit_point is smaller or equal to the cyl radius;
}

double	limit_cyl(t_objs *obj, t_data *d, t_vector p, double t)
{
	t_vector	hit_p;
	t_vector	ra1;
	t_vector	ra2;

	if (t <= 0)
		return (-1);
	hit_p = vec_sum(p, vec_scale(d->cur_p.pos, t));
	ra1 = vec_sum(obj->cord, vec_scale(obj->orientation, -(obj->height / 2)));
	ra2 = vec_sum(obj->cord, vec_scale(obj->orientation, obj->height / 2));
	if (dot_product(vec_sub(hit_p, ra1), obj->orientation) > 0 && \
		dot_product(vec_sub(hit_p, ra2), obj->orientation) < 0)
		return (t);
	return (-1);
}

double	calculate_scaler_cy(t_objs *obj, t_data *d, t_vector p)
{
	double		a;
	double		b;
	double		c;
	double		t;
	t_vector	va;
	t_vector	ra;
	t_vector	v;

	v = d->cur_p.pos;
	// printf("v");
	//check v and obj->cord, are they the right values
	va = cross_product(cross_product(obj->orientation, v), obj->orientation);
	ra = cross_product(cross_product(obj->orientation, \
	vec_sub(p, obj->cord)), obj->orientation);
	a = dot_product(va, va);
	b = dot_product(vec_scale(ra, 2), va);
	c = dot_product(ra, ra) - (obj->diameter / 2) * (obj->diameter / 2);
	//if the tube is not hit, check for the caps;
	t = limit_cyl(obj, d, p, quadratic_solve(a, b, c));
	if (t < 0)
		return (calculate_scaler_caps(obj, d, p));
	// t = quadratic_solve(a, b, c);
	obj->normal = calculate_cyl_normal(obj, vec_sum(d->cam->cord, \
	vec_scale(v, t)));
	return (t);
}

double	calculate_scaler_cy_maha(t_objs *obj, t_data *d, t_vector p)
{
	double		A, B, C;
	double		a, b, c;
	double		k, j, i;
	double		xp, yp, zp;
	double		xm, ym, zm;
	double		t;
	// t_vector	va;
	// t_vector	ra;
	t_vector	v;

	v = d->cur_p.pos;
	a = obj->orientation.x;
	b = obj->orientation.y;
	c = obj->orientation.z;
	i = d->cur_p.pos.x;
	j = d->cur_p.pos.y;
	k = d->cur_p.pos.z;
	xp = p.x;
	yp = p.y;
	zp = p.z;
	xm = obj->cord.x;
	ym = obj->cord.y;
	zm = obj->cord.z;

	A = k * k * (b * b + a * a) + \
		j * j * (c * c + a * a) + \
		i * i * (c * c + b * b) - \
		2 * (b * c * k * j + a * c * i * k + a * b * j * i);
	B = 2 * (k * zp * (b * b + a * a) + j * yp * (c * c + a * a) + i * xp * (c * c + b * b) + \
		k * (-b * b * zm + b * c * ym + a * c * xm - a * a * zm) + \
		j * (b * c * zm - c * c * ym - a * a * ym + a * b * xm) + \
		i * (-c * c * xm + a * c * zm + a * b * ym - b * b * xm) - \
		b * c * (k * yp + j * zp) - \
		a * c * (i * zp + k * xp) - \
		a * b * (j * xp + i * yp));
	C = (-obj->diameter / 2) * (obj->diameter / 2) * (a * a + b * b + c * c) + \
		b * b * (zm * zm + xm * xm) + \
		c * c * (ym * ym + xm * xm) + \
		a * a * (zm * zm + ym * ym) + \
		2 * (- b * c * zm * ym - a * c * zm * xm - a * b * ym * xm) + \
		zp * zp * (b * b + a * a) + \
		yp * yp * (a * a + c * c) + \
		xp * xp * (c * c + b * b) + \
		2 * (zp * (-b * b * zm + b * c * ym + a * c * xm - a * a * zm) + \
			yp * (b * c * zm - c * c * ym - a * a * ym + a * b * xm) + \
			xp * (-c * c * xm + a * c * zm + a * b * ym - b * b * xm) - \
			b * c * zp * yp - a * c * xp * zp - a * b * xp * yp);
	t = limit_cyl(obj, d, p, quadratic_solve(A, B, C));
	if (t < 0)
		return (calculate_scaler_caps(obj, d, p));
	// t = quadratic_solve(a, b, c);
	obj->normal = calculate_cyl_normal(obj, vec_sum(d->cam->cord, \
	vec_scale(v, t)));
	return (t);
}
