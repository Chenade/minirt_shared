/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_sys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:58:31 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/27 23:58:31 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_saved(t_data *d)
{
	int		fd;
	int		i;

	fd = open("./maps/newMap.rt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < d->nbr_objs)
	{
		((void (*)(t_data*, int, int))(d->objs[i].print_func))(d, i, fd);
		i += 1;
	}
	close(fd);
	printf("Saved\n");
	return (0);
}
