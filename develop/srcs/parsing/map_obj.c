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

int	map_check_sphere(t_data *d, char **line, int index)
{
	double	diameter;

	if (ft_array_len(line) != 4)
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	diameter = ft_strtod(line[2]);
	if (diameter > 1000)
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	d->objs[index].radius = diameter / 2;
	if (set_color(&d->objs[index].color, line[3]))
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	init_sp(d, index);
	return (0);
}

int	map_check_plane(t_data *d, char **line, int index)
{
	if (ft_array_len(line) != 4)
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	if (set_dir(&d->objs[index].dir, line[2]))
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	d->objs[index].dir = normalize_vect(d->objs[index].dir);
	if (set_color(&d->objs[index].color, line[3]))
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	init_pl(d, index);
	return (0);
}

int	map_check_cylinder(t_data *d, char **line, int index)
{
	double	diameter;
	double	height;

	if (ft_array_len(line) != 6)
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	diameter = ft_strtod(line[3]);
	if (diameter > 1000)
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	d->objs[index].radius = diameter / 2;
	height = ft_strtod(line[4]);
	d->objs[index].height = height;
	if (set_dir(&d->objs[index].dir, line[2]))
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	if (set_color(&d->objs[index].color, line[5]))
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	init_cyl(d, index);
	return (0);
}
