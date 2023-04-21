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
r0 = pos of the point of emission (cam->pos);
rt = pos of obj;
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

we check for intersections on both those planes,
inside the radius of the cylinder;
*/

t_vector	calculate_cyl_normal(t_objs *cyl, t_vector hit_pt)
{
	double		t;
	t_vector	pt;
	t_vector	cyl_bottom;

	cyl_bottom = cyl->cap_2;
	t = dot_product(vec_sub(hit_pt, cyl_bottom), cyl->dir);
	pt = vec_sum(cyl_bottom, vec_scale(cyl->dir, t));
	return (normalize_vect(vec_sub(hit_pt, pt)));
}

double	hit_cap(t_vector dir, t_data *d, t_vector p, t_vector center, double radius)
{
	double		t;
	t_vector	v;

	v = d->cur_p.dir;
	t = (-dir.x * (p.x - center.x) \
		- dir.y * (p.y - center.y) \
		- dir.z * (p.z - center.z)) / \
		(dir.x * v.x + dir.y * v.y + dir.z * v.z);
	// hit_point = p + t*v; vec_sum(p, vec_scaler(v, t));
	// dist between hit_point and center <= radius;
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

	t1 = hit_cap(cyl->dir, d, p, cyl->cap_1, cyl->radius);
	t2 = hit_cap(vec_scale(cyl->dir, -1), d, p, cyl->cap_2, cyl->radius);
	res = smallest_positive(t1, t2);
	if (res == t1)
		cyl->normal = cyl->dir;
	else
		cyl->normal = vec_scale(cyl->dir, -1);
	return (res);
	// for each plane, check for collisions;
	// then check if the distance between the pos of plane (center
	// of the cap) and the hit_point is smaller or equal to the cyl radius;
}

double	limit_cyl(t_objs *obj, t_data *d, t_vector p, double t)
{
	t_vector	hit_p;
	t_vector	ra1;
	t_vector	ra2;

	if (t <= 0)
		return (-1);
	hit_p = vec_sum(p, vec_scale(d->cur_p.dir, t));
	ra1 = vec_sum(obj->pos, vec_scale(obj->dir, -(obj->height / 2)));
	ra2 = vec_sum(obj->pos, vec_scale(obj->dir, obj->height / 2));
	if (dot_product(vec_sub(hit_p, ra1), obj->dir) > 0 && \
		dot_product(vec_sub(hit_p, ra2), obj->dir) < 0)
		return (t);
	return (-1);
}

double	calculate_scaler_cy(t_objs *obj, t_data *d, t_vector p)
{
	double		a;
	double		b;
	double		c;
	double		t;
	t_vector	v;

	v = d->cur_p.dir;
	obj->math.va = cross_product(cross_product(obj->dir, v), obj->dir);
	obj->math.ra = cross_product(cross_product(obj->dir, \
	vec_sub(p, obj->pos)), obj->dir);
	a = dot_product(obj->math.va, obj->math.va);
	b = dot_product(vec_scale(obj->math.ra, 2), obj->math.va);
	c = dot_product(obj->math.ra, obj->math.ra) - obj->radius * obj->radius;
	t = limit_cyl(obj, d, p, quadratic_solve(a, b, c, obj));
	// if the tube is not hit, check for the caps :
	if (t < 0)
		return (calculate_scaler_caps(obj, d, p));
	obj->normal = calculate_cyl_normal(obj, vec_sum(d->cam->pos, \
	vec_scale(v, t)));
	return (t);
}

// -------------------------------DEPRECATED-----------------------------------

// void	init_math(t_objs *obj)
// {
// 	obj->math.radius_2 = obj->radius * obj->radius;
// 	obj->math.a = obj->dir.x;
// 	obj->math.b = obj->dir.y;
// 	obj->math.c = obj->dir.z;
// 	obj->math.xm = obj->pos.x;
// 	obj->math.ym = obj->pos.y;
// 	obj->math.zm = obj->pos.z;
// 	obj->math.a_2 = obj->math.a * obj->math.a;
// 	obj->math.b_2 = obj->math.b * obj->math.b;
// 	obj->math.c_2 = obj->math.c * obj->math.c;
// 	obj->math.xm_2 = obj->math.xm * obj->math.xm;
// 	obj->math.ym_2 = obj->math.ym * obj->math.ym;
// 	obj->math.zm_2 = obj->math.zm * obj->math.zm;
// }

// void	update_math(t_objs *obj, t_data *d, t_vector p)
// {
// 	obj->math.i = d->cur_p.dir.x;
// 	obj->math.j = d->cur_p.dir.y;
// 	obj->math.k = d->cur_p.dir.z;
// 	obj->math.xp = p.x;
// 	obj->math.yp = p.y;
// 	obj->math.zp = p.z;
// 	obj->math.i_2 = obj->math.i * obj->math.i;
// 	obj->math.j_2 = obj->math.j * obj->math.j;
// 	obj->math.k_2 = obj->math.k * obj->math.k;
// 	obj->math.xp_2 = obj->math.xp * obj->math.xp;
// 	obj->math.yp_2 = obj->math.yp * obj->math.yp;
// 	obj->math.zp_2 = obj->math.zp * obj->math.zp;
// }

// double	calculate_scaler_cy_maha(t_objs *obj, t_data *d, t_vector p)
// {
// 	double		t;
// 	t_math		m;
// 	t_vector	v;

// 	v = d->cur_p.dir;
// 	update_math(obj, d, p);
// 	m = obj->math;
// 	m._a = m.k_2 * (m.b_2 + m.a_2) + \
// 		m.j_2 * (m.c_2 + m.a_2) + \
// 		m.i_2 * (m.c_2 + m.b_2) - \
// 		2 * (m.b * m.c * m.k * m.j + m.a * m.c * m.i * m.k + m.a * m.b * m.j * m.i);
// 	m._b = 2 * (m.k * m.zp * (m.b_2 + m.a_2) + m.j * m.yp * (m.c_2 + m.a_2) + m.i * m.xp * (m.c_2 + m.b_2) + \
// 		m.k * (-m.b_2 * m.zm + m.b * m.c * m.ym + m.a * m.c * m.xm - m.a_2 * m.zm) + \
// 		m.j * (m.b * m.c * m.zm - m.c_2 * m.ym - m.a_2 * m.ym + m.a * m.b * m.xm) + \
// 		m.i * (-m.c_2 * m.xm + m.a * m.c * m.zm + m.a * m.b * m.ym - m.b_2 * m.xm) - \
// 		m.b * m.c * (m.k * m.yp + m.j * m.zp) - \
// 		m.a * m.c * (m.i * m.zp + m.k * m.xp) - \
// 		m.a * m.b * (m.j * m.xp + m.i * m.yp));
// 	m._c = -obj->math.radius_2 * (m.a_2 + m.b_2 + m.c_2) + \
// 		m.b_2 * (m.zm_2 + m.xm_2) + \
// 		m.c_2 * (m.ym_2 + m.xm_2) + \
// 		m.a_2 * (m.zm_2 + m.ym_2) + \
// 		2 * (- m.b * m.c * m.zm * m.ym - m.a * m.c * m.zm * m.xm - m.a * m.b * m.ym * m.xm) + \
// 		m.zp_2 * (m.b_2 + m.a_2) + \
// 		m.yp_2 * (m.a_2 + m.c_2) + \
// 		m.xp_2 * (m.c_2 + m.b_2) + \
// 		2 * (m.zp * (-m.b_2 * m.zm + m.b * m.c * m.ym + m.a * m.c * m.xm - m.a_2 * m.zm) + \
// 		m.yp * (m.b * m.c * m.zm - m.c_2 * m.ym - m.a_2 * m.ym + m.a * m.b * m.xm) + \
// 		m.xp * (-m.c_2 * m.xm + m.a * m.c * m.zm + m.a * m.b * m.ym - m.b_2 * m.xm) - \
// 		m.b * m.c * m.zp * m.yp - m.a * m.c * m.xp * m.zp - m.a * m.b * m.xp * m.yp);
// 	t = limit_cyl(obj, d, p, quadratic_solve(m._a, m._b, m._c, obj));
// 	if (t < 0)
// 		return (calculate_scaler_caps(obj, d, p));
// 	obj->normal = calculate_cyl_normal(obj, vec_sum(d->cam->pos, \
// 	vec_scale(v, t)));
// 	return (t);
// }
