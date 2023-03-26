/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:32:35 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/17 19:32:36 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pixel	hit_sphere(struct s_objs *obj, struct s_data *d, int x, int y)
{
	double	delta;
	double	scaler;
	t_pixel	pixel;

	// printf("center : %f, %f, %f\n", obj->cord.x, obj->cord.y, obj->cord.z);
	// printf("light : %f, %f, %f\n", d->light.pos.x, d->light.pos.y, d->light.pos.z);
	delta = check_solutions(obj, d, x, y);
	if (delta < 0)
	{
		pixel.scaler = -1;
		return (pixel);
	}
	scaler = calculate_scaler_sp(obj, d, x, y);
	// set_vector(&pixel.pos, "1,1,1");
	pixel.pos = d->cur_p.pos;
	pixel.scaler = scaler;
	pixel.norm = calculate_sp_norm(obj->cord, vec_sum(d->cam.cord, vec_scale(pixel.pos, pixel.scaler)));
	pixel.color = obj->color;
	// printf("%s : 255, 0, 255\n", __func__);
	return (pixel);
}

t_pixel	hit_plane(struct s_objs *obj, struct s_data *d, int x, int y)
{
	t_pixel	pixel;
	double	vn;
	double	scaler;

	obj->orientation = normalize_vect(obj->orientation);
	vn = check_vn2(obj, d, x, y);
	if (vn >= -0.00001 && vn <= 0.00001)
	{
		pixel.scaler = -1;
		return (pixel);
	}
	scaler = calculate_scaler_pl2(obj, d, x, y);
	if (scaler < 0)
	{
		pixel.scaler = -1;
		return (pixel);
	}
	// set_vector(&pixel.pos, "2,2,2");
	pixel.pos = d->cur_p.pos;
	pixel.scaler = scaler;
	pixel.norm = obj->orientation;
	pixel.color = obj->color;
	// printf("%s\n", __func__);
	return (pixel);
}

t_pixel	hit_cylinder(struct s_objs *obj, struct s_data *d, int x, int y)
{
	t_pixel	pixel;

	(void)obj;
	(void)d;
	(void)x;
	(void)y;
	set_vector(&pixel.pos, "10000,10000,10000");
	set_color(&pixel.color, "0,0,0");
	// printf("%s\n", __func__);
	return (pixel);
}
