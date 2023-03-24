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

double	get_norm(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

double	quadratic_disrciminant(double a, double b, double c)
{
	printf("d: %f\n", b * b - 4 * (a * c));
	return (b * b - 4 * (a * c));
}

double	quadratic_solve(double a, double b, double c)
{
	double	delta;
	double	s1;
	double	s2;

	delta = quadratic_disrciminant(a, b, c);
	if (delta > 0)
	{
		s1 = (-b - sqrt(delta)) / (2 * a);
		s2 = (-b + sqrt(delta)) / (2 * a);
		if (s1 < s2)
			return (s1);
		return (s2); // check for the smallest !! -> positive <- !!;
	}
	return (-b / (2 * a));
}

double	check_solutions(t_objs *obj, t_data *d, double x, double y)
{
	double		a;
	double		b;
	double		c;
	double		norm;
	t_vector	v;

	norm = get_norm(-WIDTH / 2 + x, HEIGHT / 2 - y, d->cam_len);
	v.x = (-WIDTH / 2 + x) / norm;
	v.y = (HEIGHT / 2 - y) / norm;
	v.z = (d->cam_len) / norm;
	a = v.x * v.x + v.y * v.y + v.z * v.z;
	b = 2 * (0 - v.x * obj->cord.x + 0 - v.y * \
		obj->cord.y + 0 - v.z * obj->cord.z);
	c = (0 - obj->cord.x) * (0 - obj->cord.x) + (0 - obj->cord.y) \
		* (0 - obj->cord.y) + (0 - obj->cord.z) * (0 - obj->cord.z) \
		- (obj->diameter / 2) * (obj->diameter / 2);
	// need to replace 0 by the coordinates of the camera !!!
	return (quadratic_disrciminant(a, b, c));
}

double	calculate_time(t_objs *obj, t_data *d, double x, double y)
{
	double		a;
	double		b;
	double		c;
	double		norm;
	t_vector	v;

	norm = get_norm(-WIDTH / 2 + x, HEIGHT / 2 - y, d->cam_len);
	v.x = (-WIDTH / 2 + x) / norm;
	v.y = (HEIGHT / 2 - y) / norm;
	v.z = (d->cam_len) / norm;
	a = v.x * v.x + v.y * v.y + v.z * v.z;
	b = 2 * (0 - v.x * obj->cord.x + 0 - v.y * \
		obj->cord.y + 0 - v.z * obj->cord.z);
	c = (0 - obj->cord.x) * (0 - obj->cord.x) + (0 - obj->cord.y) \
		* (0 - obj->cord.y) + (0 - obj->cord.z) * (0 - obj->cord.z) \
		- (obj->diameter / 2) * (obj->diameter / 2);
	// need to replace 0 by the coordinates of the camera !!!
	return (quadratic_solve(a, b, c));
}
