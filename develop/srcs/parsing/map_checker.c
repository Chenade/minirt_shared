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

	ratio = ft_strtod(line[1]);
	if (ratio < 0 || ratio > 1)
		return (1);
	d->objs[index].ratio = ratio;
	if (set_color(&d->objs[index].color, line[2]))
		return (1);
	if (line[3])
		return (1);
	return (0);
}

int	map_check_light(t_data *d, char **line, int index)
{
	double	ratio;

	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	ratio = ft_strtod(line[2]);
	if (ratio < 0 || ratio > 1)
		return (1);
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	return (0);
}

int	map_check_sphere(t_data *d, char **line, int index)
{
	double	diameter;

	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	diameter = ft_strtod(line[2]);
	if (diameter > 1000)
		return (1);
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	if (line[4])
		return (1);
	d->objs[index].collision_func = collosion_sphere;
	return (0);
}

int	map_check_plane(t_data *d, char **line, int index)
{
	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	if (set_orientation(&d->objs[index].orientation, line[2]))
		return (1);
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	if (line[4])
		return (1);
	d->objs[index].collision_func = collosion_plane;
	return (0);
}

int	map_check_cylinder(t_data *d, char **line, int index)
{
	double	diameter;
	double	height;

	if (set_vector(&d->objs[index].cord, line[1]))
		return (1);
	diameter = ft_strtod(line[2]);
	if (diameter > 1000)
		return (1);
	height = ft_strtod(line[3]);
	if (height > 1000)
		return (1);
	if (set_orientation(&d->objs[index].orientation, line[2]))
		return (1);
	if (set_color(&d->objs[index].color, line[4]))
		return (1);
	if (line[5])
		return (1);
	d->objs[index].collision_func = collosion_cylinder;
	return (0);
}
