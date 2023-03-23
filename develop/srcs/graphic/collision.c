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
// t_pixel	*collosion_sphere(t_objs obj, t_data *d)
t_pixel	collosion_sphere(struct s_objs *obj, struct s_data *d)
{
	t_pixel	pixel;

	(void)obj;
	(void)d;
	set_vector(&pixel.pos, "1,1,1");
	set_color(&pixel.color, "255,255,255");
	printf("%s\n", __func__);
	return (pixel);
}

// t_pixel	*collosion_plane(t_objs obj, t_data *d)
t_pixel	collosion_plane(struct s_objs *obj, struct s_data *d)
{
	t_pixel	pixel;

	(void)obj;
	(void)d;
	set_vector(&pixel.pos, "1,1,1");
	set_color(&pixel.color, "255,255,255");
	printf("%s\n", __func__);
	return (pixel);
}

// t_pixel	*collosion_cylinder(t_objs obj, t_data *d)
t_pixel	collosion_cylinder(struct s_objs *obj, struct s_data *d)
{
	t_pixel	pixel;

	(void)obj;
	(void)d;
	set_vector(&pixel.pos, "1,1,1");
	set_color(&pixel.color, "255,255,255");
	printf("%s\n", __func__);
	return (pixel);
}
