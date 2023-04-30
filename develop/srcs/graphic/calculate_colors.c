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
	t_vector	color_ratio;

	color_ratio.x = (double)p->color.r / 255;
	color_ratio.y = (double)p->color.g / 255;
	color_ratio.z = (double)p->color.b / 255;
	c->r += color_ratio.x * d->ambient->color.r * d->ambient->intensity;
	c->g += color_ratio.y * d->ambient->color.g * d->ambient->intensity;
	c->b += color_ratio.z * d->ambient->color.b * d->ambient->intensity;
}

t_color	put_diffuse(t_pixel *p, t_color *c, t_data *d)
{
	double		angle;
	t_vector	color_ratio;

	angle = dot_product(d->cur_p.dir, p->normal);
	if (angle < 0)
		angle = 0;
	color_ratio.x = (double)p->color.r / 255;
	color_ratio.y = (double)p->color.g / 255;
	color_ratio.z = (double)p->color.b / 255;
	c->r = color_ratio.x * d->light->color.r \
	* d->light->intensity * angle;
	c->g = color_ratio.y * d->light->color.g \
	* d->light->intensity * angle;
	c->b = color_ratio.z * d->light->color.b \
	* d->light->intensity * angle;
	return (*c);
}

t_color	put_specular(t_pixel *p, t_color *c, t_data *d)
{
	double		dot;
	double		angle;
	double		re;
	t_vector	r;
	t_vector	color_ratio;

	dot = dot_product(d->cur_p.dir, p->normal);
	if (dot < 0)
		return (*c);
	angle = acos((dot) / (get_vec_norm(d->cur_p.dir) * get_vec_norm(p->normal)));
	r = vec_sum(vec_scale(d->cur_p.dir, -1), vec_scale(p->normal, 2 * dot));
	re = dot_product(r, vec_scale(normalize_vect(vec_sub(p->pos, d->cam->pos)), -1));
	if (re < 0)
		re = 0;
	re = re * re * re * re * re * re * re * re * re * re * re * re * re;
	// re = re * re;
	color_ratio.x = (double)p->color.r / 255;
	color_ratio.y = (double)p->color.g / 255;
	color_ratio.z = (double)p->color.b / 255;
	c->r += d->light->color.r * d->light->intensity * 0.5 * re * (0.5 * color_ratio.x + 0.5);
	c->g += d->light->color.g * d->light->intensity * 0.5 * re * (0.5 * color_ratio.x + 0.5);
	c->b += d->light->color.b * d->light->intensity * 0.5 * re * (0.5 * color_ratio.x + 0.5);
	return (*c);
}
