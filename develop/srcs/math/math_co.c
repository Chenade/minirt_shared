/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_co.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:49:02 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/25 18:49:05 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Cone equations :

first, intersection with an infinite cone (looks like an hourglass):

at^2 + bt + c = 0;

a = va.va - vs^2 * (radius^2 / h^2);

b = 2ra.va + 2 * w * vs * (radius^2 / h^2);

c = ra.ra - w^2 * (radius^2 / h^2);

v = direction vector of the ray;
r_origin = pos of the point of emission (cam->pos for example);
obj_pos = position of the obj;
s = direction vector of the cone;
R = radius of cone;

va = (s x v x s);
vs = v.s;
h = height of the cone;
ra = s x (r_origin - obj_pos) x s;
h0 = (r_origin - obj_pos).s;
w = h - h0;

* : "x" means cross product. see vectors functions;

--------------------------------------------------

to limit the cone,

we have to check for 2 conditions :

(hit_p - ra1).s > 0         &&         (hit_p - ra2).s < 0

hit_p = r_origin + v*t (so the position of the point of intersection between
		the ray and the cone at t time in the v direction starting at r_origin,
		r_origin being 'p' in my functions);

ra1 & ra2 = positions of the 2 extremities of the central axis
			relative to the starting point of the ray (r_origin or 'p');

s = same as above, direction vector of the cone;

--------------------------------------------------

intersection with the base of the cone :

pos of pl : pos of the cone + direction vector(normalized) * -height / 2;

direction of pl : -direction vector of cyl (normalized);

we have :

	pl_pos = vec_sum((cone.pos, vec_scale(cone.dir, -height / 2));
	pl_dir = vec_scale(cone_dir, -1);

we check for intersections on the plane, xinside the radius of the cone;
*/

/*
cases :

cyl :
2 solutions;
1 solution and no cap hit;
1 solution and a cap hit;
0 solution and caps hit;
0 solution;

cone :
2 solutions and base hit;
2 solutions;
1 solution and base hit;
1 solution;
0 solution
*/

t_vector	calculate_cone_normal(t_objs *cone, t_vector hit_pt)
{
	double		t;
	t_vector	pt;
	t_vector	base;
	t_vector	rota;
	t_vector	res;

	base = cone->cap_2;
	t = dot_product(vec_sub(hit_pt, base), cone->dir);
	pt = vec_sum(base, vec_scale(cone->dir, t));
	res = normalize_vect(vec_sub(hit_pt, pt));
	rota = cross_product(res, cone->dir);
	rot_v_around_v(&res, &rota, cone->cone_angle);
	return (res);
}

double	hit_base(t_objs *cone, t_data *d, t_vector p)
{
	double		t;
	t_vector	v;
	t_vector	dir;
	t_vector	center;

	v = d->cur_p.dir;
	dir = vec_scale(cone->dir, -1);
	center = cone->cap_2;
	t = (-dir.x * (p.x - center.x) \
		- dir.y * (p.y - center.y) \
		- dir.z * (p.z - center.z)) / \
		(dir.x * v.x + dir.y * v.y + dir.z * v.z);
	if (t > 0 && \
	fabs(get_vec_norm(vec_sub(center, vec_sum(p, vec_scale(v, t))))) < \
	cone->radius)
		return (t);
	return (-1);
}

double	calculate_s_base(t_objs *cone, t_data *d, t_vector p)
{
	double	t;

	t = hit_base(cone, d, p);
	cone->math.base_normal = vec_scale(cone->dir, -1);
	return (t);
}

double	limit_cone(t_objs *obj, t_data *d, t_vector p, double t)
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

double	calculate_scaler_co(t_objs *obj, t_data *d, t_vector p)
{
	t_math		*m;

	cone_math(d, obj, p);
	m = &obj->math;
	m->s_base = calculate_s_base(obj, d, p);
	m->a = dot_product(m->va, m->va) - (m->vs * m->vs) * m->rh_2;
	m->b = dot_product(vec_scale(m->ra, 2), m->va) + 2 * m->w * m->vs * m->rh_2;
	m->c = dot_product(m->ra, m->ra) - m->w_2 * m->rh_2;
	quadratic_solve_cyl_co(d, obj, p);
	if (m->s1 > 0)
		m->s1 = limit_cone(obj, d, p, m->s1);
	if (m->s2 > 0)
		m->s2 = limit_cone(obj, d, p, m->s2);
	return (smallest_visible_positive_co(obj, d, p, obj->math));
}



/*
TODO

bonus :
	- CHECK INSIDE CONES !!
	- hide objects;
	- add specular;
	- textures;
	- multiple lights;
	- maybe improve colors;

opti : partition space, fast inverse sqrt, cos ?;

DONE :
	- cones;
*/
