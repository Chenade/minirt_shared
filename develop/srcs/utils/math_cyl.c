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

a = va.va     -> va = (s x v x s);

b = 2ra.va;   -> ra = s x (r0 - rt) x s;

c = ra.ra - R^2;

v = direction vector of the ray;
r0 = cord of the point of emission (cam->cord);
rt = cord of obj;
s = direction vector of the tube;
R = radius of tube;

------------------------------------------------

now we limit the tube with planes

...

*/

double	limit_cyl(t_objs *obj, t_data *d, t_vector p, double t)
{
	t_vector	hit_p;
	t_vector	ra1;
	t_vector	ra2;

	hit_p = vec_sum(p, vec_scale(d->cur_p.pos, t));
	// ra1 = vec_scale(normalize_vect(obj->cord), -obj->height);
	// ra2 = vec_scale(normalize_vect(obj->cord), obj->height);
	ra1 = vec_scale(obj->cord, -obj->height);
	ra2 = vec_scale(obj->cord, obj->height);
	if (dot_product(vec_sub(hit_p, ra1), obj->orientation) > 0 && \
		dot_product(vec_sub(hit_p, ra2), obj->orientation) < 0)
		return (printf("test\n"), t);
	return (-1);
}

double	check_solutions_cy(t_objs *obj, t_data *d, t_vector p)
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
	return (quadratic_discriminant(a, b, c));
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
	// return (limit_cyl(obj, d, p, quadratic_solve(a, b, c)));
	return (quadratic_solve(a, b, c));
}

