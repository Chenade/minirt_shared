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
	// d->objs[index].type = DEF;
	d->ambient.color = d->objs[index].color;
	d->ambient.ratio = d->objs[index].ratio;
	d->objs[index].keyboard_func = key_light;
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
	d->light.pos = d->objs[index].cord;
	ratio = ft_strtod(line[2]);
	if (ratio < 0 || ratio > 1)
		return (1);
	d->light.ratio = ratio;
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	// d->objs[index].type = DEF;
	d->light.color = d->objs[index].color;
	d->objs[index].diameter = 10;
	d->objs[index].collision_func = hit_light;
	d->objs[index].keyboard_func = key_light;
	return (0);
}

int	map_check_sphere(t_data *d, char **line, int index)
{
	double	diameter;

	if (ft_array_len(line) != 4)
		return (1);
	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	diameter = ft_strtod(line[2]);
	if (diameter > 1000)
		return (1);
	d->objs[index].diameter = diameter;
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	// d->objs[index].type = SP;
	d->objs[index].collision_func = hit_sphere;
	d->objs[index].keyboard_func = key_sphere;
	return (0);
}

int	map_check_plane(t_data *d, char **line, int index)
{
	if (ft_array_len(line) != 4)
		return (1);
	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	if (set_orientation(&d->objs[index].orientation, line[2]))
		return (1);
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	// d->objs[index].type = PL;
	d->objs[index].collision_func = hit_plane;
	d->objs[index].keyboard_func = key_plane;
	return (0);
}

int	map_check_cylinder(t_data *d, char **line, int index)
{
	double	diameter;
	double	height;

	if (ft_array_len(line) != 5)
		return (1);
	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	diameter = ft_strtod(line[2]);
	if (diameter > 1000)
		return (1);
	d->objs[index].diameter = diameter;
	height = ft_strtod(line[3]);
	if (height > 1000)
		return (1);
	if (set_orientation(&d->objs[index].orientation, line[2]))
		return (1);
	if (set_color(&d->objs[index].color, line[4]))
		return (1);
	// d->objs[index].type = CYL;
	d->objs[index].collision_func = hit_cylinder;
	d->objs[index].keyboard_func = key_cylinder;
	return (0);
}
