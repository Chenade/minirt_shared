/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:32:28 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/17 19:32:29 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pixel	min_objects(int i, t_pixel p1, t_pixel p2)
{
	if (i == 0 && p1.pos.z < p2.pos.z)
	{
		return (p1);
	}
	return (p2);
}

int	ray_tracing(t_data *d, int x, int y)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;
	int		color;

	(void)x;
	(void)y;
	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		if (objs.collision_func)
			pixel = min_objects(i, pixel, (objs.collision_func(&objs, d)));
		i ++;
	}
	color = encode_rgb(pixel.color);
	return (color);
}
