/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transla_rota.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:16:04 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/21 21:16:06 by znogueir         ###   ########.fr       */
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

Formula for rotating vector v around axis w by a given angle :

	v_rot = v*cos(angle) + (w x v)*sin(angle) + w(w . v)*(1 - cos(angle));

(Rodrigues' formula
https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula).

t_vector	rot_v_arount_v(t_vector v, t_vector w, double angle)
{
	t_vector	v_rot;

	v_rot = vec_sum(vec_sum(vec_scale(v, cos(angle)),
	vec_scale(cross_product(w, v), sin(angle))),
	vec_scale(w, (dot_product(w, v) * (1 - cos(angle)))));
	return (v_rot);
}

check the vectors_ops2.c file.

---------------------------------------------------------------------------

Translations (for any object, including the camera):

We just add the unit vector of the camera axis corresponding (times a factor
if we want to) to the pos of the object.

That gives us :

obj->pos = vec_sum(obj->pos, vec_scale(cam_axis, n));

n being an arbitrary scaler, and cam_axis any x, y or z axis vector of the
camera.
*/

int	ft_move(t_data *d, t_objs *obj, int keysym)
{
	if (keysym == XK_Left)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir_x, -STEP)), 1);
	else if (keysym == XK_Right)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir_x, STEP)), 1);
	else if (keysym == XK_Up)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir, STEP)), 1);
	else if (keysym == XK_Down)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir, -STEP)), 1);
	else if (keysym == XK_y)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir_y, STEP)), 1);
	else if (keysym == XK_h)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir_y, -STEP)), 1);
	return (0);
}

int	ft_dir(t_data *d, t_objs *obj, int keycode)
{
	if (keycode == XK_q)
		return (rot_v_arount_v(&obj->dir, &d->cam->dir, 0.1), 1);
	if (keycode == XK_e)
		return (rot_v_arount_v(&obj->dir, &d->cam->dir, -0.1), 1);
	if (keycode == XK_s)
		return (rot_v_arount_v(&obj->dir, &d->cam->dir_x, -0.1), 1);
	if (keycode == XK_w)
		return (rot_v_arount_v(&obj->dir, &d->cam->dir_x, 0.1), 1);
	if (keycode == XK_d)
		return (rot_v_arount_v(&obj->dir, &d->cam->dir_y, -0.1), 1);
	if (keycode == XK_a)
		return (rot_v_arount_v(&obj->dir, &d->cam->dir_y, 0.1), 1);
	return (0);
}

int	ft_rotate_cam(t_objs *obj, int keycode)
{
	if (keycode == XK_r)
		return (obj->dir = vec_scale(obj->dir, -1), \
		obj->dir_x = vec_scale(obj->dir_x, -1), 1);
	if (keycode == XK_q)
		return (rot_v_arount_v(&obj->dir_x, &obj->dir, 0.05), \
		rot_v_arount_v(&obj->dir_y, &obj->dir, 0.05), 1);
	if (keycode == XK_e)
		return (rot_v_arount_v(&obj->dir_x, &obj->dir, -0.05), \
		rot_v_arount_v(&obj->dir_y, &obj->dir, -0.05), 1);
	if (keycode == XK_s)
		return (rot_v_arount_v(&obj->dir, &obj->dir_x, 0.05), \
		rot_v_arount_v(&obj->dir_y, &obj->dir_x, 0.05), 1);
	if (keycode == XK_w)
		return (rot_v_arount_v(&obj->dir, &obj->dir_x, -0.05), \
		rot_v_arount_v(&obj->dir_y, &obj->dir_x, -0.05), 1);
	if (keycode == XK_d)
		return (rot_v_arount_v(&obj->dir, &obj->dir_y, 0.05), \
		rot_v_arount_v(&obj->dir_x, &obj->dir_y, 0.05), 1);
	if (keycode == XK_a)
		return (rot_v_arount_v(&obj->dir, &obj->dir_y, -0.05), \
		rot_v_arount_v(&obj->dir_x, &obj->dir_y, -0.05), 1);
	return (0);
}

/*
NEW SYSTEM

- Move around : Arrow keys;
- Move up and down : Y+/H-;

- Rotations :
	- Around X : W+ / S-;
	- Around Y : D -> / A <-;
	- Around Z : E tilt -> / Q tilt <-;
- Lenght (for cyl) : U+ / I-;
- Radius (cyl & sp) : J+ / K-;
*/
