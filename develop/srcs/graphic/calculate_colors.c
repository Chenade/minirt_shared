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

void	get_color(t_pixel pixel, t_pixel *p, t_data *d)
{
	// t_vector	v;
	double		angle;
	t_color		ret;
	t_vector	color_ratio;

	ret = (t_color){0, 0, 0, 0};
	// v = normalize_vect(vec_sub(d->light->pos, p->pos));
	angle = dot_product(d->cur_p.dir, p->normal);
	if (angle < 0)
		angle = 0;
	color_ratio.x = (double)p->color.r / 255;
	color_ratio.y = (double)p->color.g / 255;
	color_ratio.z = (double)p->color.b / 255;
	ret.r = color_ratio.x * d->ambient->color.r * d->ambient->intensity;
	ret.g = color_ratio.y * d->ambient->color.g * d->ambient->intensity;
	ret.b = color_ratio.z * d->ambient->color.b * d->ambient->intensity;
	if (pixel.scaler > d->cur_p.dir.norm || pixel.scaler < 0)
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
