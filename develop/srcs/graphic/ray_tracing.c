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

t_pixel	max_scaler(int i, t_pixel p1, t_pixel p2)
{
	if (i != 0 && (fabs(p1.scaler)) > (fabs(p2.scaler)) && p1.scaler > 0)
	{
		return (p1);
	}
	if (p2.scaler > 0)
		return (p2);
	return (p1);
}

void	reset_color_ratio(t_pixel *p)
{
	int	highest;

	if (p->color.r >= p->color.g && p->color.r >= p->color.b)
		highest = p->color.r;
	else if (p->color.g >= p->color.b)
		highest = p->color.g;
	else
		highest = p->color.b;
	if (highest <= 0)
		return ;
	p->color.r = 255 * p->color.r / highest;
	p->color.g = 255 * p->color.g / highest;
	p->color.b = 255 * p->color.b / highest;
}

void	get_color(t_pixel pixel, t_pixel *p, t_data *d, double d_to_l)
{
	t_vector	v;
	double		angle;
	t_color		ret;
	t_vector	color_ratio;

	ret = (t_color){0, 0, 0, 0};
	v = normalize_vect(vec_sub(d->light->pos, vec_sum(d->cam->pos, \
	vec_scale(p->dir, p->scaler))));
	angle = dot_product(v, p->normal);
	if (angle < 0)
		angle = 0;
	color_ratio.x = (double)p->color.r / 255;
	color_ratio.y = (double)p->color.g / 255;
	color_ratio.z = (double)p->color.b / 255;
	ret.r = color_ratio.x * d->ambient->color.r * d->ambient->intensity;
	ret.g = color_ratio.y * d->ambient->color.g * d->ambient->intensity;
	ret.b = color_ratio.z * d->ambient->color.b * d->ambient->intensity;
	if (pixel.scaler > d_to_l || pixel.scaler < 0)
	{
		ret.r += color_ratio.x * d->light->color.r * d->light->intensity * angle;
		ret.g += color_ratio.y * d->light->color.g * d->light->intensity * angle;
		ret.b += color_ratio.z * d->light->color.b * d->light->intensity * angle;
	}
	p->color.r = ret.r;
	p->color.g = ret.g;
	p->color.b = ret.b;
	if (p->color.r > 255 || p->color.g > 255 || p->color.b > 255)
		reset_color_ratio(p);
}

void	trace_shadow(t_pixel *p, t_data *d, t_vector v, double d_to_l)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;

	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	// set_color(&pixel.color, "0,0,0");
	pixel.scaler = -1;
	d->cur_p.dir = v;
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		if (objs.shadow_func)
		{
			pixel = min_scaler(i, pixel,
					((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p))
						objs.shadow_func)(&objs, d, vec_sum(d->cam->pos, \
						vec_scale(vec_sum(p->dir, vec_scale(p->normal, 0.00001)), p->scaler))));
		}
		i++;
	}
	get_color(pixel, p, d, d_to_l);
}

void	get_shadow(t_pixel *p, t_data *d)
{
	t_vector	v;
	double		d_to_l;

	v = vec_sub(d->light->pos, vec_sum(d->cam->pos, \
	vec_scale(p->dir, p->scaler)));
	d_to_l = get_norm(v.x, v.y, v.z);
	v = normalize_vect(v);
	trace_shadow(p, d, v, d_to_l);
}

int	ray_tracing(t_data *d, int x, int y)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;
	int		color;

	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	// set_color(&pixel.color, "0,0,0");
	pixel.scaler = -1;
	pixel.is_light = 0;
	get_cur_vec(d, x, y);
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		if (objs.collision_func)
		{
			pixel = min_scaler(i, pixel,
					((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p))
						objs.collision_func)(&objs, d, d->cam->pos));
		}
		i++;
	}
	if (pixel.scaler > 0 && pixel.is_light == 0)
		get_shadow(&pixel, d);
	color = encode_rgb(pixel.color);
	return (color);
}
