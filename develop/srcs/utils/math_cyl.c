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

*/

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
	t_vector	va;
	t_vector	ra;
	t_vector	v;

	v = d->cur_p.pos;
	va = cross_product(cross_product(obj->orientation, v), obj->orientation);
	ra = cross_product(cross_product(obj->orientation, \
	vec_sub(p, obj->cord)), obj->orientation);
	a = dot_product(va, va);
	b = dot_product(vec_scale(ra, 2), va);
	c = dot_product(ra, ra) - (obj->diameter / 2) * (obj->diameter / 2);
	return (limit_cyl(obj, d, p, quadratic_solve(a, b, c)));
}
