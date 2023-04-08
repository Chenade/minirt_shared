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
	if (set_vector(&d->objs[index].pos, line[1]))
		return (1);
	// d->cam.pos = d->objs[index].pos;
	if (set_dir(&d->objs[index].dir, line[2]))
		return (1);
	// d->cam.dir = d->objs[index].dir;
	if (d->objs[index].dir.x == 0 && d->objs[index].dir.y == 0
		&& d->objs[index].dir.z == 0)
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
	double	intensity;

	if (d->nbr_ambient != 0)
		return (1);
	d->nbr_ambient += 1;
	if (ft_array_len(line) != 3)
		return (1);
	intensity = ft_strtod(line[1]);
	if (intensity < 0 || intensity > 1)
		return (1);
	d->objs[index].intensity = intensity;
	if (set_color(&d->objs[index].color, line[2]))
		return (1);
	d->objs[index].type = DEF;
	d->objs[index].color = d->objs[index].color;
	d->objs[index].intensity = d->objs[index].intensity;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_ambient;
	d->objs[index].print_func = print_ambient;
	d->ambient = &d->objs[index];
	return (0);
}

int	map_check_light(t_data *d, char **line, int index)
{
	double	intensity;

	if (d->nbr_light != 0)
		return (1);
	d->nbr_light += 1;
	if (ft_array_len(line) != 4)
		return (1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (1);
	intensity = ft_strtod(line[2]);
	if (intensity < 0 || intensity > 1)
		return (1);
	d->objs[index].intensity = intensity;
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	d->objs[index].type = DEF;
	d->objs[index].radius = 3;
	d->objs[index].collision_func = hit_light;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_light;
	d->objs[index].print_func = print_light;
	d->light = &d->objs[index];
	d->objs[index].math.radius_2 = \
	d->objs[index].radius * d->objs[index].radius;
	return (0);
}
