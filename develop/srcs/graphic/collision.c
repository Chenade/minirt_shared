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

t_pixel	hit_sphere(struct s_objs *obj, struct s_data *d, t_vector p)
{
	double	scaler;
	t_pixel	pixel;

	pixel.is_light = 0;
	scaler = calculate_scaler_sp(obj, d, p);
	pixel.scaler = scaler;
	if (scaler == -1)
		return (pixel);
	pixel.pos = d->cur_p.pos;
	pixel.color = obj->color;
	pixel.normal = calculate_sp_normal(obj->cord, vec_sum(d->cam->cord, \
	vec_scale(pixel.pos, pixel.scaler)));
	return (pixel);
}

t_pixel	sphere_shadow(struct s_objs *obj, struct s_data *d, t_vector p)
{
	double	scaler;
	t_pixel	pixel;

	scaler = calculate_scaler_sp(obj, d, p);
	pixel.scaler = scaler;
	// printf("%s\n", __func__);
	return (pixel);
}

t_pixel	hit_plane(struct s_objs *obj, struct s_data *d, t_vector p)
{
	t_pixel	pixel;
	double	scaler;
	// double	vn;

	obj->orientation = normalize_vect(obj->orientation);
	// vn = check_vn2(obj, d);
	pixel.is_light = 0;
	// if (vn >= -0.00001 && vn <= 0.00001)
	// {
	// 	pixel.scaler = -1;
	// 	return (pixel);								??????????
	// 	//need to fix this cause its weird;
	// }
	scaler = calculate_scaler_pl2(obj, d, p);
	if (scaler < 0)
	{
		pixel.scaler = -1;
		return (pixel);
	}
	pixel.scaler = scaler;
	pixel.pos = d->cur_p.pos;
	pixel.normal = obj->orientation;
	pixel.color = obj->color;
	// printf("%s\n", __func__);
	return (pixel);
}

t_pixel	plane_shadow(struct s_objs *obj, struct s_data *d, t_vector p)
{
	t_pixel	pixel;
	double	scaler;
	// double	vn;

	obj->orientation = normalize_vect(obj->orientation);
	// vn = check_vn2(obj, d);
	// if (vn >= -0.00001 && vn <= 0.00001)
	// {
	// 	pixel.scaler = -1;
	// 	return (pixel);								??????????
	// 	//need to fix this cause its weird;
	// }
	scaler = calculate_scaler_pl2(obj, d, p);
	if (scaler < 0)
	{
		pixel.scaler = -1;
		return (pixel);
	}
	pixel.scaler = scaler;
	// printf("%s\n", __func__);
	return (pixel);
}

t_pixel	hit_cylinder(struct s_objs *obj, struct s_data *d, t_vector p)
{
	double	scaler;
	t_pixel	pixel;

	pixel.is_light = 0;
	scaler = calculate_scaler_cy(obj, d, p);
	pixel.scaler = scaler;
	if (scaler == -1)
		return (pixel);
	pixel.pos = d->cur_p.pos;
	pixel.normal = calculate_cyl_normal(obj, vec_sum(d->cam->cord, \
	vec_scale(pixel.pos, pixel.scaler)));
	pixel.color = obj->color;
	return (pixel);
}

t_pixel	cylinder_shadow(struct s_objs *obj, struct s_data *d, t_vector p)
{
	t_pixel	pixel;

	(void)obj;
	(void)d;
	(void)p;
	// set_vector(&pixel.pos, "10000,10000,10000");
	// set_color(&pixel.color, "0,0,0");
	pixel.is_light = 0;
	printf("%s\n", __func__);
	return (pixel);
}

t_pixel	hit_light(struct s_objs *obj, struct s_data *d, t_vector p)
{
	// double	delta;
	double	scaler;
	t_pixel	pixel;

	pixel.is_light = 1;
	scaler = calculate_scaler_sp(obj, d, p);
	pixel.scaler = scaler;
	if (scaler == -1)
		return (pixel);
	pixel.pos = d->cur_p.pos;
	pixel.normal = calculate_sp_normal(obj->cord, vec_sum(d->cam->cord, \
	vec_scale(pixel.pos, pixel.scaler)));
	pixel.color = obj->color;
	return (pixel);
}
