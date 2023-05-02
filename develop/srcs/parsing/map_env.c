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

/*
|tan(180 - fov/2) * WIDTH/2|

-> |tan(pi - fov(rad)/2) * WIDTH/2|

rad trans -> deg * pi / 180
*/

void	get_cam_len(t_data *d)
{
	d->cam_len = fabs(tan(PI / 2 - \
	((d->fov * PI / 180) / 2)) * (WIDTH / 2));
}

int	map_check_cam(t_data *d, char **line, int index)
{
	double	fov;

	if (d->nbr_camera != 0)
		return (print_err("Error\n: Invalid Map: More than 1 Camera", d), 1);
	d->nbr_camera += 1;
	if (ft_array_len(line) != 4)
		return (print_err("Error\n: Invalid Map: Camera Format", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Camera Position", d), 1);
	if (set_dir(&d->objs[index].dir, line[2]))
		return (print_err("Error\n: Invalid Map: Camera Vector", d), 1);
	if (d->objs[index].dir.x == 0 && d->objs[index].dir.y == 0
		&& d->objs[index].dir.z == 0)
		return (print_err("Error\n: Invalid Map: Camera vector", d), 1);
	fov = ft_strtod(line[3]);
	if (fov < 0 || fov > 180)
		return (print_err("Error\n: Invalid Map: Camera", d), 1);
	d->fov = fov;
	init_cam(d, index);
	return (0);
}

int	map_check_ambient(t_data *d, char **line, int index)
{
	double	intensity;

	if (d->nbr_ambient != 0)
		return (print_err("Error\n: Invalid Map: Ambinent Light", d), 1);
	d->nbr_ambient += 1;
	if (ft_array_len(line) != 3)
		return (print_err("Error\n: Invalid Map: Ambinent Light", d), 1);
	intensity = ft_strtod(line[1]);
	if (intensity < 0 || intensity > 1)
		return (print_err("Error\n: Invalid Map: Ambinent Light", d), 1);
	d->objs[index].intensity = intensity;
	if (set_color(&d->objs[index].color, line[2]))
		return (1);
	init_ambient(d, index);
	return (0);
}

int	map_check_light(t_data *d, char **line, int index)
{
	double	intensity;

	// if (d->nbr_light != 0)
	// 	return (print_err("Error\n: Invalid Map: Light", d), 1);
	d->nbr_light += 1;
	if (ft_array_len(line) != 4)
		return (print_err("Error\n: Invalid Map: Light", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Light", d), 1);
	intensity = ft_strtod(line[2]);
	if (intensity < 0 || intensity > 1)
		return (print_err("Error\n: Invalid Map: Light", d), 1);
	d->objs[index].intensity = intensity;
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	init_light(d, index);
	return (0);
}
