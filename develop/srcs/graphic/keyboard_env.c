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

int	key_camera(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	i = (i || ft_rotate_cam(&d->objs[d->index], keysym));
	// if (keysym == XK_m)
	// {
	// 	d->display_gui = (d->display_gui == 0);
	// 	i = 1;
	// }
	return (i);
}

int	key_light(t_data *d, int keysym)
{
	int	i;

	i = ft_move(d, &d->objs[d->index], keysym);
	return (i);
}
