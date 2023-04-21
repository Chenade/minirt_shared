/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:13:03 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:13:06 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Rotations :

For the camera, to rotate around an axis we just rotate the two other axes
around the rotation axis.

For the object, we rotate the direction vector around the camera axis
corresponding.

In order to do so, we need a function to rotate a vector around another one.

Formula for rotating vector v around axis w by a given angle: 

v_rot = v*cos(angle) + (w x v)*sin(angle) + w(w . v)*(1 - cos(angle));

t_vector	rot_v_arount_v(t_vector v, t_vector w, double angle)
{
	t_vector	v_rot;

	v_rot = 
	vec_sum(vec_sum(vec_scale(v, cos(angle)), 
	vec_scale(cross_product(w, v), sin(angle))), 
	vec_scale(w, (dot_product(w, v) * (1 - cos(angle)))));
	return (v_rot);
}

---------------------------------------------------------------------------

Translations (for any object, including the camera):

We just add the unit vector of the camera axis corresponding (times a factor
if we want to) to the pos of the object.

That gives us :

obj->pos = vec_sum(obj->pos, vec_scale(cam_axis, n));

n being an arbitrary scaler, and cam_axis any x, y or z axis vector of the
camera.
*/

int	key_saved(t_data *d)
{
	int		fd;
	int		i;

	fd = open("./maps/newMap.rt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (printf("Unable to create new map.\n"), 0);
	i = 0;
	while (i < d->nbr_objs)
	{
		((void (*)(t_data *, int, int))(d->objs[i].print_func))(d, i, fd);
		i += 1;
	}
	close(fd);
	printf("Saved\n");
	return (0);
}

int	key_camera(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	i = (i || ft_rotate_cam(&d->objs[d->index], keysym));
	return (i);
}

int	key_light(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	return (i);
}
