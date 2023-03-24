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
	t_pixel	pixel;

	if (check_solutions(obj, d, x, y) < 0)
	{
		set_vector(&pixel.pos, "1,1,1");
		printf("%s : 255, 255, 255\n", __func__);
		return (set_color(&pixel.color, "0,0,0"), pixel);
	}
	calculate_time(obj, d, x, y);
	set_vector(&pixel.pos, "1,1,1");
	set_color(&pixel.color, "255,0,255");
	// printf("%s : 255, 0, 255\n", __func__);
	return (pixel);
}

t_pixel	hit_plane(struct s_objs *obj, struct s_data *d, int x, int y)
{
	t_pixel	pixel;

	(void)obj;
	(void)d;
	(void)x;
	(void)y;
	set_vector(&pixel.pos, "1,1,1");
	set_color(&pixel.color, "0,0,0");
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
	set_vector(&pixel.pos, "1,1,1");
	set_color(&pixel.color, "0,0,0");
	// printf("%s\n", __func__);
	return (pixel);
}
