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
		vec_scale(d->cam->dir_y, STEP)), 1);
	else if (keysym == XK_Down)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir_y, -STEP)), 1);
	else if (keysym == XK_z)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir, STEP)), 1);
	else if (keysym == XK_x)
		return (obj->pos = vec_sum(obj->pos, \
		vec_scale(d->cam->dir, -STEP)), 1);
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
