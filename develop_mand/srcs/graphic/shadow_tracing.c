/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_tracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:45:36 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/08 23:45:38 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_inside_objs(t_data *d)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;

	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	d->cur_p.dir = vector(1, 0, 0);
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		objs.from_light = 1;
		if (objs.shadow_func)
		{
			((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p))
			objs.shadow_func)(&objs, d, d->light->pos);
		}
		i++;
	}
}

void	trace_shadow(t_pixel *p, t_data *d, t_vector v)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;

	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	pixel.scaler = -1;
	d->cur_p.dir = v;
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		objs.from_light = 0;
		if (objs.shadow_func)
		{
			pixel = min_scaler(i, pixel,
					((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p))
						objs.shadow_func)(&objs, d, vec_sum(d->cam->pos, \
						vec_scale(vec_sum(p->dir, \
						vec_scale(p->normal, 0.00001)), p->scaler))));
		}
		if (pixel.scaler > 0 && pixel.scaler < v.norm)
			return ((void)put_ambient(pixel, p, d));
		i++;
	}
	put_diffuse(pixel, p, d);
}
// pixel.pos = vec_sum(d->cam->pos, vec_scale(pixel.dir, pixel.scaler));

void	get_shadow(t_pixel *p, t_data *d)
{
	t_vector	v;

	v = vec_sub(d->light->pos, p->pos);
	v = normalize_vect(v);
	trace_shadow(p, d, v);
}

// void	get_shadow(t_pixel *p, t_data *d)
// {
// 	t_vector	v;
// 	// double		d_to_l;

// 	v = vec_sub(d->light->pos, p->pos);
// 	// d_to_l = get_norm(v.x, v.y, v.z);
// 	v = normalize_vect(v);
// 	trace_shadow(p, d, v);
// }