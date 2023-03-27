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

// t_pixel	min_objects(int i, t_pixel p1, t_pixel p2)
// {
// 	if (i != 0 && p1.pos.z < p2.pos.z)
// 	{
// 		return (p1);
// 	}
// 	return (p2);
// }

/*
- dot_product;
- get_norm;
*/

void	get_color(t_pixel *p, t_data *d)
{
	t_vector	v;
	double		norm1;
	double		norm2;
	double		angle;

	v = vec_sub(d->light->cord, vec_sum(d->cam->cord, \
	vec_scale(p->pos, p->scaler)));
	v = normalize_vect(v);
	norm1 = get_norm(v.x, v.y, v.z);
	norm2 = get_norm(p->norm.x, p->norm.y, p->norm.z);
	if (norm1 == 0 || norm2 == 0)
		return ;
	angle = acos(dot_product(v, p->norm) / (norm1 * norm2));
	if (angle > PI / 2)
		angle = PI / 2;
	angle = 1 - (angle / (PI / 2));
	p->color.r *= (d->light->color.r * d->light->ratio / 255) * angle;
	p->color.g *= (d->light->color.g * d->light->ratio / 255) * angle;
	p->color.b *= (d->light->color.b * d->light->ratio / 255) * angle;
}

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

// t_pixel	hit_light(struct s_objs *obj, struct s_data *d, t_pixel pixel)
// {
// 	(void)obj;
// 	(void)d;
// 	// printf("%s\n", __func__);
// 	return (pixel);
// }

int	ray_tracing(t_data *d, int x, int y)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;
	int		color;

	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	set_color(&pixel.color, "0,0,0");
	pixel.scaler = -1;
	pixel.is_light = 0;
	get_cur_vec(d, x, y);
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		if (objs.collision_func)
		{
			pixel = min_scaler(i, pixel,
					((t_pixel (*)(struct s_objs *, struct s_data *, int, int))
						objs.collision_func)(&objs, d, x, y));
		}
		i++;
	}
	if (pixel.is_light == 0)
		get_color(&pixel, d);
	// pixel = hit_light(&objs, d, pixel);
	color = encode_rgb(pixel.color);
	return (color);
}
