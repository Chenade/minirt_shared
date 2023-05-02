/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:25:57 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/22 17:25:59 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Those functions check if a point is inside an object.

We need to know if the camera is inside (or on the other side of a plane)
an object in order to invert the normals.

We also need to know if the light is inside or not, in order to cut
the light or not, depending on where the camera is :

- Cam is inside an object :
	invert the normals of the object;

- Light is inside an object :
	- Cam is inside the same object : normal behaviour;
	- Cam is outside this object : no diffuse light;
- Light is outside :
	- Cam is outside too : normal behaviour;
	- Cam is inside an object : no diffuse light;

*/

int	check_inside_sp(t_objs *obj, t_vector p)
{
	if (get_vec_norm(vec_sub(p, obj->pos)) <= obj->radius)
		return (1);
	return (0);
}

int	check_side_pl(t_objs *obj, t_vector p)
{
	if (dot_product(vec_sub(p, obj->pos), obj->dir) < 0)
		return (1);
	return (0);
}

int	check_inside_cy(t_objs *obj, t_vector p)
{
	t_vector	p_to_center;
	t_vector	project;
	t_vector	project_to_p;

	p_to_center = vec_sub(p, obj->pos);
	project = vec_scale(obj->dir, dot_product(p_to_center, obj->dir));
	if (get_vec_norm(vec_sub(project, obj->pos)) > (obj->height / 2))
		return (0);
	project_to_p = vec_sub(p, project);
	if (get_vec_norm(project_to_p) <= obj->radius)
		return (1);
	return (0);
}

int	check_inside_co(t_objs *obj, t_vector p)
{
	double		proj_len;
	t_vector	p_to_center;
	t_vector	project;
	t_vector	project_to_p;

	p_to_center = vec_sub(p, obj->pos);
	proj_len = dot_product(p_to_center, obj->dir);
	project = vec_scale(obj->dir, proj_len);
	if (get_vec_norm(vec_sub(project, obj->pos)) > (obj->height / 2))
		return (0);
	project_to_p = vec_sub(p, project);
	if (get_vec_norm(project_to_p) < (obj->radius * \
	(1 - (proj_len + obj->height / 2) / obj->height)))
		return (1);
	return (0);
}
