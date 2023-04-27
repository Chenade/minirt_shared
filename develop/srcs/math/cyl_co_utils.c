/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_co_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:53:13 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/27 02:53:15 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cone_math(t_data *d, t_objs *obj, t_vector p)
{
	obj->math.radius_2 = obj->radius * obj->radius;
	obj->math.vs = dot_product(d->cur_p.dir, obj->dir);
	obj->math.h0 = dot_product(vec_sub(p, obj->cap_2), obj->dir);
	obj->math.w = obj->height - obj->math.h0;
	obj->math.w_2 = obj->math.w * obj->math.w;
	obj->math.rh_2 = obj->math.radius_2 / (obj->height * obj->height);
	obj->math.va = cross_product(cross_product(obj->dir, d->cur_p.dir), \
				obj->dir);
	obj->math.ra = cross_product(cross_product(obj->dir, \
				vec_sub(p, obj->pos)), obj->dir);
}

void	empty(void)
{
}

void	quadratic_solve_cyl_co(t_data *d, t_objs *obj, t_vector p)
{
	double	delta;
	t_math	*m;

	(void)d;
	(void)p;
	m = &obj->math;
	delta = quadratic_discriminant(m->a, m->b, m->c);
	if (delta < 0)
		return (m->s1 = -1, m->s2 = -1, empty());
	if (delta > 0)
	{
		m->s1 = (-m->b - sqrt(delta)) / (2 * m->a);
		m->s2 = (-m->b + sqrt(delta)) / (2 * m->a);
		return ;
	}
	m->s1 = -m->b / (2 * m->a);
	m->s2 = -1;
}

double	smallest_visible_positive_co(t_objs *obj, t_data *d, t_vector p, \
		t_math m)
{
	if (m.s1 < 0 && m.s2 < 0 && m.s_base < 0)
		return (-1);
	if (m.s2 < 0 && m.s1 > 0)
	{
		if (m.s1 < m.s_base)
			return (obj->normal = calculate_cone_normal(obj, \
			vec_sum(p, vec_scale(d->cur_p.dir, m.s1))), m.s1);
		return (obj->normal = m.base_normal, m.s_base);
	}
	if (m.s1 < 0 && m.s2 > 0)
	{
		if (m.s2 < m.s_base)
			return (obj->normal = calculate_cone_normal(obj, \
			vec_sum(p, vec_scale(d->cur_p.dir, m.s2))), m.s2);
		return (obj->normal = m.base_normal, m.s_base);
	}
	if (m.s1 < m.s2)
		return (obj->normal = calculate_cone_normal(obj, \
		vec_sum(p, vec_scale(d->cur_p.dir, m.s1))), m.s1);
	return (obj->normal = calculate_cone_normal(obj, \
	vec_sum(p, vec_scale(d->cur_p.dir, m.s2))), m.s2);
}

double	smallest_visible_positive_cyl(t_objs *obj, t_data *d, t_vector p, \
		t_math m)
{
	if (m.s1 < 0 && m.s2 < 0 && m.s_base < 0)
		return (-1);
	if (m.s1 < 0 && m.s2 < 0)
		return (obj->normal = m.base_normal, m.s_base);
	if (m.s2 < 0 && m.s1 > 0)
	{
		if (m.s1 < m.s_base)
			return (obj->normal = calculate_cyl_normal(obj, \
			vec_sum(p, vec_scale(d->cur_p.dir, m.s1))), m.s1);
		return (obj->normal = m.base_normal, m.s_base);
	}
	if (m.s1 < 0 && m.s2 > 0)
	{
		if (m.s2 < m.s_base)
			return (obj->normal = calculate_cyl_normal(obj, \
			vec_sum(p, vec_scale(d->cur_p.dir, m.s2))), m.s2);
		return (obj->normal = m.base_normal, m.s_base);
	}
	if (m.s1 < m.s2)
		return (obj->normal = calculate_cyl_normal(obj, \
		vec_sum(p, vec_scale(d->cur_p.dir, m.s1))), m.s1);
	return (obj->normal = calculate_cyl_normal(obj, \
	vec_sum(p, vec_scale(d->cur_p.dir, m.s2))), m.s2);
}
