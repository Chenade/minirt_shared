/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collision_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:06:12 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/16 14:06:13 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	map_check_cam(t_data *d, char **line, int index)
{
	double	fov;

	if (d->nbr_camera != 0)
		return (1);
	d->nbr_camera += 1;
	if (ft_array_len(line) != 4)
		return (1);
	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	// d->cam.cord = d->objs[index].cord;
	if (set_orientation(&d->objs[index].orientation, line[2]))
		return (1);
	// d->cam.orientation = d->objs[index].orientation;
	if (d->objs[index].orientation.x == 0 && d->objs[index].orientation.y == 0
		&& d->objs[index].orientation.z == 0)
		return (1);
	fov = ft_strtod(line[3]);
	if (fov < 0 || fov > 180)
		return (1);
	d->fov = fov;
	d->objs[index].type = DEF;
	d->objs[index].keyboard_func = key_camera;
	d->objs[index].gui_func = gui_camera;
	d->objs[index].print_func = print_camera;
	d->cam = &d->objs[index];
	return (0);
}

int	map_check_ambient(t_data *d, char **line, int index)
{
	double	ratio;

	if (d->nbr_ambient != 0)
		return (1);
	d->nbr_ambient += 1;
	if (ft_array_len(line) != 3)
		return (1);
	ratio = ft_strtod(line[1]);
	if (ratio < 0 || ratio > 1)
		return (1);
	d->objs[index].ratio = ratio;
	if (set_color(&d->objs[index].color, line[2]))
		return (1);
	d->objs[index].type = DEF;
	d->objs[index].color = d->objs[index].color;
	d->objs[index].ratio = d->objs[index].ratio;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_ambient;
	d->objs[index].print_func = print_ambient;
	d->ambient = &d->objs[index];
	return (0);
}

int	map_check_light(t_data *d, char **line, int index)
{
	double	ratio;

	if (d->nbr_light != 0)
		return (1);
	d->nbr_light += 1;
	if (ft_array_len(line) != 4)
		return (1);
	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	ratio = ft_strtod(line[2]);
	if (ratio < 0 || ratio > 1)
		return (1);
	d->objs[index].ratio = ratio;
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	d->objs[index].type = DEF;
	d->objs[index].diameter = 6;
	d->objs[index].collision_func = hit_light;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_light;
	d->objs[index].print_func = print_light;
	d->light = &d->objs[index];
	return (0);
}
