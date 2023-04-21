/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:10:35 by znogueir          #+#    #+#             */
/*   Updated: 2023/03/23 20:10:46 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
direction vector for pixel 0,0 :
z = cam_len;
x = WIDTH / 2;
y = HEIGHT / 2;

for each pixel we only need to increment the vector by 1 in x for the lines and
1 in y for the collumns to get every direction vector;

don't forget to normalize;
*/

/*
sphere formula : (v = direction vector, p = point of origin (0,0,0 probably),
r = radius of sphere)
a = vx^2 + vy^2 + vz^2;
b = 2(px * vx) + 2(py * vy) + 2(pz * vz);
c = px^2 + py^2 + pz^2 - r^2;
*/

/*
quadratic equations :
delta (discriminant) = b^2 - 4*a*c;

if (delta > 0)
	2 solutions :
	s1 = (-b - sqrt(delta)) / (2*a);
	s2 = (-b + sqrt(delta)) / (2*a);
else if (delta == 0)
	1 solution :
	s = -b / (2*a);
else
	no solution;
*/

int	check_if_inside(t_objs *obj, double s1, double s2)
{
	if ((s1 > 0 && s2 < 0) || (s2 > 0 && s1 < 0))
	{
		if (obj->from_light == 1)
			return (obj->light_is_inside = 1);
		return (obj->cam_is_inside = 1);
	}
	if (obj->from_light == 1)
		return (obj->light_is_inside = 0);
	return (obj->cam_is_inside = 0);
}

double	smallest_positive(double n1, double n2)
{
	if ((fabs(n1)) < (fabs(n2)) && n1 > 0)
	{
		return (n1);
	}
	if (n2 > 0)
		return (n2);
	return (n1);
}

t_vector	calculate_sp_normal(t_vector center, t_vector hit_point)
{
	return (normalize_vect(vec_sub(hit_point, center)));
}

double	quadratic_discriminant(double a, double b, double c)
{
	return (b * b - 4 * (a * c));
}

double	quadratic_solve(double a, double b, double c, t_objs *obj)
{
	double	delta;
	double	s1;
	double	s2;

	(void)obj;
	delta = quadratic_discriminant(a, b, c);
	if (delta < 0)
		return (-1);
	if (delta > 0)
	{
		s1 = (-b - sqrt(delta)) / (2 * a);
		s2 = (-b + sqrt(delta)) / (2 * a);
		// check_if_inside(obj, s1, s2);
		return (smallest_positive(s1, s2));
	}
	return (-b / (2 * a));
}

double	calculate_scaler_sp(t_objs *obj, t_data *d, t_vector p)
{
	double		a;
	double		b;
	double		c;
	t_vector	v;

	v = d->cur_p.dir;
	a = v.x * v.x + v.y * v.y + v.z * v.z;
	b = 2 * (p.x * v.x - v.x * obj->pos.x + \
		p.y * v.y - v.y * obj->pos.y + \
		p.z * v.z - v.z * obj->pos.z);
	c = (p.x - obj->pos.x) * (p.x - obj->pos.x) + \
		(p.y - obj->pos.y) * (p.y - obj->pos.y) + \
		(p.z - obj->pos.z) * (p.z - obj->pos.z) - \
		obj->math.radius_2;
	return (quadratic_solve(a, b, c, obj));
}
