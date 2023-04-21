/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_ops2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:46:33 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/08 23:46:35 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_norm(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

double	get_vec_norm(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.y * v2.z - (v1.z * v2.y);
	v.y = v1.z * v2.x - (v1.x * v2.z);
	v.z = v1.x * v2.y - (v1.y * v2.x);
	if (v.x > -0.000001 && v.x < 0.000001)
		v.x = 0.0;
	if (v.y > -0.000001 && v.y < 0.000001)
		v.y = 0.0;
	if (v.z > -0.000001 && v.z < 0.000001)
		v.z = 0.0;
	return (v);
}

double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	normalize_vect(t_vector v)
{
	double		norm;
	t_vector	w;

	norm = get_norm(v.x, v.y, v.z);
	w.x = v.x / norm;
	w.y = v.y / norm;
	w.z = v.z / norm;
	w.norm = norm;
	return (w);
}
