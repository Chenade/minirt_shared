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

t_pixel	min_scaler(int i, t_pixel p1, t_pixel p2)
{
	if (i != 0 && (fabs(p1.scaler)) < (fabs(p2.scaler)) && p1.scaler > 0)
	{
		return (p1);
	}
	if (p2.scaler > 0)
		return (p2);
	return (p1);
}
/**/
// t_pixel	max_scaler(int i, t_pixel p1, t_pixel p2)
// {
// 	if (i != 0 && (fabs(p1.scaler)) > (fabs(p2.scaler)) && p1.scaler > 0)
// 	{
// 		return (p1);
// 	}
// 	if (p2.scaler > 0)
// 		return (p2);
// 	return (p1);
// }

int	ray_tracing(t_data *d, int x, int y)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;
	int		color;

	i = -1;
	ft_bzero(&pixel, sizeof(t_pixel));
	pixel.scaler = -1;
	pixel.is_light = 0;
	get_cur_vec(d, x, y);
	while (++i < d->nbr_objs)
	{
		objs = d->objs[i];
		objs.from_light = 0;
		if (objs.collision_func && objs.is_hidden == 0)
			pixel = min_scaler(i, pixel,
					((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p))
						objs.collision_func)(&objs, d, d->cam->pos));
	}
	pixel.pos = vec_sum(d->cam->pos, vec_scale(pixel.dir, pixel.scaler));
	if (pixel.scaler > 0 && pixel.is_light == 0)
		get_shadow(&pixel, d);
	color = encode_rgb(pixel.color);
	return (color);
}
