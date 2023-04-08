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
		return (obj->pos.x -= STEP, 1);
	else if (keysym == XK_Right)
		return (obj->pos.x += STEP, 1);
	else if (keysym == XK_Up)
		return (obj->pos.y += STEP, 1);
	else if (keysym == XK_Down)
		return (obj->pos.y -= STEP, 1);
	else if (keysym == XK_z)
		return (obj->pos.z += STEP, 1);
	else if (keysym == XK_x)
		return (obj->pos.z -= STEP, 1);
	return (0);
}

int	ft_dir(t_objs *obj, int keysym)
{
	if (keysym == XK_q && (obj->dir.x >= -1.05))
		return (obj->dir.x -= 0.075, 1);
	else if (keysym == XK_a && (obj->dir.x <= 0.95))
		return (obj->dir.x += 0.075, 1);
	else if (keysym == XK_w && (obj->dir.y >= -1.05))
		return (obj->dir.y -= 0.075, 1);
	else if (keysym == XK_s && (obj->dir.y <= 0.95))
		return (obj->dir.y += 0.075, 1);
	else if (keysym == XK_e && (obj->dir.z >= -1.05))
		return (obj->dir.z -= 0.075, 1);
	else if (keysym == XK_d && (obj->dir.z <= 0.95))
		return (obj->dir.z += 0.075, 1);
	return (0);
}

int	key_camera(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = (i || ft_dir(&d->objs[d->index], keysym));
	return (i);
}

int	key_light(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	return (i);
}
