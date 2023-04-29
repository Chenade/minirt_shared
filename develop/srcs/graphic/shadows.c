/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:45:50 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/08 23:45:54 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pixel	sphere_shadow(struct s_objs *obj, struct s_data *d, t_vector p)
{
	double	scaler;
	t_pixel	pixel;

	scaler = calculate_scaler_sp(obj, d, p);
	pixel.scaler = scaler;
	return (pixel);
}

t_pixel	plane_shadow(struct s_objs *obj, struct s_data *d, t_vector p)
{
	t_pixel	pixel;
	double	scaler;

	obj->dir = normalize_vect(obj->dir);
	scaler = calculate_scaler_pl2(obj, d, p);
	if (scaler < 0)
	{
		pixel.scaler = -1;
		return (pixel);
	}
	pixel.scaler = scaler;
	return (pixel);
}

t_pixel	cylinder_shadow(struct s_objs *obj, struct s_data *d, t_vector p)
{
	double	scaler;
	t_pixel	pixel;

	pixel.is_light = 0;
	scaler = calculate_scaler_cy(obj, d, p);
	pixel.scaler = scaler;
	return (pixel);
}

t_pixel	cone_shadow(struct s_objs *obj, struct s_data *d, t_vector p)
{
	double	scaler;
	t_pixel	pixel;

	pixel.is_light = 0;
	scaler = calculate_scaler_co(obj, d, p);
	pixel.scaler = scaler;
	return (pixel);
}
