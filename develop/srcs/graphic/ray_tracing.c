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

	if (p->color.r == 0 && p->color.g == 0 && p->color.b == 0)
		return ;
	if (p->color.r >= p->color.g && p->color.r >= p->color.b)
		highest = p->color.r;
	else if (p->color.g >= p->color.b)
		highest = p->color.g;
	else
		highest = p->color.b;
	p->color.r = 255 * p->color.r / highest;
	p->color.g = 255 * p->color.g / highest;
	p->color.b = 255 * p->color.b / highest;
}

void	get_color(t_pixel pixel, t_pixel *p, t_data *d, double d_to_l)
{
	t_vector	v;
	double		angle;

	// (void)pixel;
	// (void)d_to_l;
	v = normalize_vect(vec_sub(d->light->cord, vec_sum(d->cam->cord, \
	vec_scale(p->pos, p->scaler))));
	angle = dot_product(v, p->normal);
	if (angle < 0)
		angle = 0;
	p->color.r *= (d->light->color.r * d->light->ratio / 255) * angle;
	p->color.g *= (d->light->color.g * d->light->ratio / 255) * angle;
	p->color.b *= (d->light->color.b * d->light->ratio / 255) * angle;
	p->color.r += (d->ambient->color.r * d->ambient->ratio / 255) * pixel.color.r;
	p->color.g += (d->ambient->color.g * d->ambient->ratio / 255) * pixel.color.g;
	p->color.b += (d->ambient->color.b * d->ambient->ratio / 255) * pixel.color.b;
	if (p->color.r > 255 || p->color.g > 255 || p->color.b > 255)
		reset_color_ratio(p);
	// printf("r : %d; g : %d; b : %d;\n", p->color.r, p->color.g, p->color.b);
	if (pixel.scaler < d_to_l && pixel.scaler > 0 && angle != 0)
	{
		p->color.r *= (d->ambient->color.r * d->ambient->ratio / 255);
		p->color.g *= (d->ambient->color.g * d->ambient->ratio / 255);
		p->color.b *= (d->ambient->color.b * d->ambient->ratio / 255);
	}
}

void	trace_shadow(t_pixel *p, t_data *d, t_vector v, double d_to_l)
{
	int		i;
	t_objs	objs;
	t_pixel	pixel;

	(void)d_to_l;
	// if (p->scaler < 0)
	// 	set_color(&p->color, "0,0,0");
	i = 0;
	ft_bzero(&pixel, sizeof(t_pixel));
	set_color(&pixel.color, "1,1,1");
	pixel.scaler = -1;
	d->cur_p.pos = v;
	while (i < d->nbr_objs)
	{
		objs = d->objs[i];
		if (objs.shadow_func)
		{
			pixel = min_scaler(i, pixel,
					((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p))
						objs.shadow_func)(&objs, d, vec_sum(d->cam->cord, \
						vec_scale(vec_sum(p->pos, vec_scale(p->normal, 0.00001)), p->scaler))));
		}
		i++;
	}
	// if (pixel.scaler < d_to_l && pixel.scaler > 0)
	// 	set_color(&p->color, "0,0,0");
	get_color(pixel, p, d, d_to_l);
}

void	get_shadow(t_pixel *p, t_data *d)
{
	t_vector	v;
	double		d_to_l;

	v = vec_sub(d->light->cord, vec_sum(d->cam->cord, \
	vec_scale(p->pos, p->scaler)));
	d_to_l = get_norm(v.x, v.y, v.z);
	v = normalize_vect(v);
	trace_shadow(p, d, v, d_to_l);
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
					((t_pixel (*)(struct s_objs *, struct s_data *, t_vector p))
						objs.collision_func)(&objs, d, d->cam->cord));
		}
		i++;
	}
	if (pixel.scaler > 0 && pixel.is_light == 0)
		get_shadow(&pixel, d);
	// get_color(&pixel, d);
	color = encode_rgb(pixel.color);
	return (color);
}
