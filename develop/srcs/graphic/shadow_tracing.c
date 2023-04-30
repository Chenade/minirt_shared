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

t_color	trace_shadow2(t_data *d, t_pixel *p)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;
	t_color	c;

	i = -1;
	ft_bzero(&c, sizeof(t_color));
	ft_bzero(&pixel, sizeof(t_pixel));
	pixel.scaler = -1;
	while (i++ < d->nbr_objs)
	{
		objs = d->objs[i];
		objs.from_light = 0;
		if (objs.shadow_func)
		{
			pixel = min_scaler(i, pixel, \
			((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p)) \
			objs.shadow_func)(&objs, d, vec_sum(d->cam->pos, \
			vec_scale(vec_sum(p->dir, \
			vec_scale(p->normal, 0.00001)), p->scaler))));
		}
		if (pixel.scaler > 0 && pixel.scaler < d->cur_p.dir.norm)
			return (ft_bzero(&c, sizeof(t_color)), c);
	}
	put_diffuse(p, &c, d);
	put_specular(p, &c, d);
	return (c);
}

void	trace_shadow(t_pixel *p, t_data *d, t_vector v)
{
	int		i;
	t_color	tmp_c;
	t_color	new_c;

	(void)v;
	i = 0;
	ft_bzero(&new_c, sizeof(t_color));
	while (i < d->nbr_objs)
	{
		if (d->objs[i].type == LIGHT)
		{
			d->light = &d->objs[i];
			d->cur_p.dir = normalize_vect(vec_sub(d->light->pos, p->pos));
			tmp_c = trace_shadow2(d, p);
			new_c.r += tmp_c.r;
			new_c.g += tmp_c.g;
			new_c.b += tmp_c.b;
		}
		i++;
	}
	put_ambient(p, d, &new_c);
	p->color = new_c;
	reset_color_ratio(p);
}

void	get_shadow(t_pixel *p, t_data *d)
{
	t_vector	v;

	v = vec_sub(d->light->pos, p->pos);
	v = normalize_vect(v);
	trace_shadow(p, d, v);
}
