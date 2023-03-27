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

int	ft_move(t_objs *obj, int keysym)
{
	if (keysym == XK_Left)
		return (obj->cord.x -= 1, 1);
	else if (keysym == XK_Right)
		return (obj->cord.x += 1, 1);
	else if (keysym == XK_Up)
		return (obj->cord.y += 1, 1);
	else if (keysym == XK_Down)
		return (obj->cord.y += 1, 1);
	else if (keysym == XK_Z)
		return (obj->cord.z += 1, 1);
	else if (keysym == XK_X)
		return (obj->cord.z += 1, 1);
	return (0);
}

int	ft_orientation(t_objs *obj, int keysym)
{
	if (keysym == XK_KP_7)
		return (obj->orientation.x -= 1, 1);
	else if (keysym == XK_KP_4)
		return (obj->orientation.x += 1, 1);
	else if (keysym == XK_KP_8)
		return (obj->orientation.y += 1, 1);
	else if (keysym == XK_KP_5)
		return (obj->orientation.y += 1, 1);
	else if (keysym == XK_KP_9)
		return (obj->orientation.z += 1, 1);
	else if (keysym == XK_KP_6)
		return (obj->orientation.z += 1, 1);
	return (0);
}

int	key_sphere(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	printf("%s: %d\n", __func__, d->index);
	return (i);
}

int	key_plane(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = ft_orientation(&d->objs[d->index], keysym);
	printf("%s: %d\n", __func__, d->index);
	return (i);
}

int	key_cylinder(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = ft_orientation(&d->objs[d->index], keysym);
	printf("%s: %d\n", __func__, d->index);
	return (i);
}

int	key_camera(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = ft_orientation(&d->objs[d->index], keysym);
	printf("%s: %d\n", __func__, d->index);
	return (i);
}

int	key_light(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	printf("%s: %d\n", __func__, d->index);
	return (i);
}
