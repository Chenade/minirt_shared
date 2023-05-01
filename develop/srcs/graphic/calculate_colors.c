/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:45:05 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/08 23:45:08 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_color_ratio(t_pixel *p)
{
	int	highest;

	if (p->color.r <= 255 && p->color.g <= 255 && p->color.b <= 255)
		return ;
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
	// p->color.r = (p->color.r > 255 ? 255 : p->color.r);
	// p->color.g = (p->color.g > 255 ? 255 : p->color.g);
	// p->color.b = (p->color.b > 255 ? 255 : p->color.b);
}

void	put_ambient(t_pixel *p, t_data *d, t_color *c)
{
	t_vector	ratio;

	ratio.x = (double)p->color.r / 255;
	ratio.y = (double)p->color.g / 255;
	ratio.z = (double)p->color.b / 255;
	c->r += ratio.x * d->ambient->color.r * d->ambient->intensity;
	c->g += ratio.y * d->ambient->color.g * d->ambient->intensity;
	c->b += ratio.z * d->ambient->color.b * d->ambient->intensity;
}

t_color	put_diffuse(t_pixel *p, t_color *c, t_data *d)
{
	double		angle;
	t_vector	ratio;

	angle = dot_product(d->cur_p.dir, p->normal);
	if (angle < 0)
		angle = 0;
	ratio.x = (double)p->color.r / 255;
	ratio.y = (double)p->color.g / 255;
	ratio.z = (double)p->color.b / 255;
	c->r = ratio.x * d->light->color.r * d->light->intensity * angle;
	c->g = ratio.y * d->light->color.g * d->light->intensity * angle;
	c->b = ratio.z * d->light->color.b * d->light->intensity * angle;
	return (*c);
}

double	get_re_pow(t_data *d, t_pixel *p, t_vector r, int n)
{
	double	re;

	re = dot_product(r, \
	vec_scale(normalize_vect(vec_sub(p->pos, d->cam->pos)), -1));
	if (re < 0)
		re = 0;
	while (n-- > 0)
	{
		re *= re;
	}
	return (re);
}

t_color	put_specular(t_pixel *p, t_color *c, t_data *d)
{
	double		dot;
	double		angle;
	double		re;
	t_vector	r;
	t_vector	ratio;

	dot = dot_product(d->cur_p.dir, p->normal);
	if (dot < 0)
		return (*c);
	angle = acos((dot) / \
	(get_vec_norm(d->cur_p.dir) * get_vec_norm(p->normal)));
	r = vec_sum(vec_scale(d->cur_p.dir, -1), vec_scale(p->normal, 2 * dot));
	re = get_re_pow(d, p, r, 4);
	if (re == 0)
		return (*c);
	ratio.x = 0.8 * (double)p->color.r / 255 + 0.8;
	ratio.y = 0.8 * (double)p->color.g / 255 + 0.8;
	ratio.z = 0.8 * (double)p->color.b / 255 + 0.8;
	c->r += d->light->color.r * d->light->intensity * 0.8 * re * ratio.x;
	c->g += d->light->color.g * d->light->intensity * 0.8 * re * ratio.y;
	c->b += d->light->color.b * d->light->intensity * 0.8 * re * ratio.z;
	return (*c);
}
