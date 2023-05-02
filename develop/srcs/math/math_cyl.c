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
Cylinder equations :

first, intersection with an infinite tube:

at^2 + bt + c = 0;

a = va.va     -> va = (s x v x s);      ->  *

b = 2ra.va;   -> ra = s x (r_origin - obj_pos) x s;

c = ra.ra - R^2;

v = direction vector of the ray;
r_origin = pos of the point of emission (cam->pos for example);
obj_pos = position of the obj;
s = direction vector of the tube;
R = radius of tube;

* : "x" means cross product. see vectors functions;

--------------------------------------------------

to limit the tube,

we have to check for 2 conditions :

(hit_p - ra1).s > 0         &&         (hit_p - ra2).s < 0

hit_p = r_origin + v*t (so the position of the point of intersection between
		the ray and the tube at t time in the v direction starting at r_origin,
		r_origin being 'p' in my functions);

ra1 & ra2 = positions of the 2 extremities of the central axis
			relative to the starting point of the ray (r_origin or 'p');

s = same as above, direction vector of the tube;

--------------------------------------------------

intersection with the caps of the cylinder :

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

double	hit_cap(t_objs *cyl, t_data *d, t_vector p, int cap)
{
	double		t;
	t_vector	v;
	double		radius;
	t_vector	center;
	t_vector	dir;

	radius = cyl->radius;
	center = cyl->cap_1;
	dir = cyl->dir;
	if (cap == 2)
	{
		center = cyl->cap_2;
		dir = vec_scale(cyl->dir, -1);
	}
	v = d->cur_p.dir;
	t = (-dir.x * (p.x - center.x) \
		- dir.y * (p.y - center.y) \
		- dir.z * (p.z - center.z)) / \
		(dir.x * v.x + dir.y * v.y + dir.z * v.z);
	if (t > 0 && \
	fabs(get_vec_norm(vec_sub(center, vec_sum(p, vec_scale(v, t))))) < radius)
		return (t);
	return (-1);
}

// for each plane, check for collisions;
// then check if the distance between the pos of plane (center
// of the cap) and the hit_point is smaller or equal to the cyl radius;
double	calculate_scaler_caps(t_objs *cyl, t_data *d, t_vector p)
{
	double	t1;
	double	t2;
	double	res;

	t1 = hit_cap(cyl, d, p, 1);
	t2 = hit_cap(cyl, d, p, 2);
	res = smallest_positive(t1, t2);
	if (res == t1)
		return (cyl->math.base_normal = cyl->dir, res);
	return (cyl->math.base_normal = vec_scale(cyl->dir, -1), res);
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
	t_math		*m;
	t_vector	v;

	m = &obj->math;
	v = d->cur_p.dir;
	m->s_base = calculate_scaler_caps(obj, d, p);
	m->va = cross_product(cross_product(obj->dir, v), obj->dir);
	m->ra = cross_product(cross_product(obj->dir, \
	vec_sub(p, obj->pos)), obj->dir);
	m->a = dot_product(m->va, m->va);
	m->b = dot_product(vec_scale(m->ra, 2), m->va);
	m->c = dot_product(m->ra, m->ra) - obj->radius * obj->radius;
	quadratic_solve_cyl_co(d, obj, p);
	if (m->s1 > 0)
		m->s1 = limit_cyl(obj, d, p, m->s1);
	if (m->s2 > 0)
		m->s2 = limit_cyl(obj, d, p, m->s2);
	return (smallest_visible_positive_cyl(obj, d, p, obj->math));
}
