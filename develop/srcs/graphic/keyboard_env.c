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

int	ft_move(t_objs *obj, int keysym)
{
	if (keysym == XK_Left)
		return (obj->cord.x -= STEP, 1);
	else if (keysym == XK_Right)
		return (obj->cord.x += STEP, 1);
	else if (keysym == XK_Up)
		return (obj->cord.y += STEP, 1);
	else if (keysym == XK_Down)
		return (obj->cord.y += STEP, 1);
	else if (keysym == XK_z)
		return (obj->cord.z += STEP, 1);
	else if (keysym == XK_x)
		return (obj->cord.z -= STEP, 1);
	return (0);
}

int	ft_orientation(t_objs *obj, int keysym)
{
	if (keysym == XK_q)
		return (obj->orientation.x -= 1, 1);
	else if (keysym == XK_a)
		return (obj->orientation.x += 1, 1);
	else if (keysym == XK_w)
		return (obj->orientation.y += 1, 1);
	else if (keysym == XK_s)
		return (obj->orientation.y += 1, 1);
	else if (keysym == XK_e)
		return (obj->orientation.z += 1, 1);
	else if (keysym == XK_d)
		return (obj->orientation.z += 1, 1);
	return (0);
}

int	key_camera(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = (i || ft_orientation(&d->objs[d->index], keysym));
	return (i);
}

int	key_light(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	return (i);
}
