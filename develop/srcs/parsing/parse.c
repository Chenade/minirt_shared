/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:32:05 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/17 19:32:06 by ykuo             ###   ########.fr       */
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
	d->cam.cord = d->objs[index].cord;
	if (set_orientation(&d->objs[index].orientation, line[2]))
		return (1);
	d->cam.orientation = d->objs[index].orientation;
	if (d->objs[index].orientation.x == 0 && d->objs[index].orientation.y == 0
		&& d->objs[index].orientation.z == 0)
		return (1);
	fov = ft_strtod(line[3]);
	if (fov < 0 || fov > 180)
		return (1);
	d->cam.fov = fov;
	d->objs[index].keyboard_func = key_camera;
	return (0);
}

int	define_obj(t_data *d, char	**tmp, int index)
{
	int	status;

	status = 1;
	printf("%s\n", tmp[0]);
	if (ft_strcmp(tmp[0], "C") == 0)
		status = map_check_cam(d, tmp, index);
	else if (ft_strcmp(tmp[0], "A") == 0)
		status = map_check_ambient (d, tmp, index);
	else if (ft_strcmp(tmp[0], "L") == 0)
		status = map_check_light (d, tmp, index);
	else if (ft_strcmp(tmp[0], "sp") == 0)
		status = map_check_sphere (d, tmp, index);
	else if (ft_strcmp(tmp[0], "pl") == 0)
		status = map_check_plane (d, tmp, index);
	else if (ft_strcmp(tmp[0], "cy") == 0)
		status = map_check_cylinder (d, tmp, index);
	else if (ft_strcmp(tmp[0], "#") == 0)
		return (0);
	ft_free_array(tmp);
	if (status)
		return (print_err("Error: Invalid Map.", d), 1);
	return (0);
}

int	process_file(t_data *d, int fd)
{
	char	*l;
	int		i;
	char	**tmp;

	while (42)
	{
		l = get_next_line (fd);
		if (!l)
			break ;
		if (*l != '\n' && *l != '#')
			ft_array_push(&d->raw, l);
		free (l);
	}
	d->nbr_objs = ft_array_len(d->raw);
	printf("nbr_objs: %d\n", d->nbr_objs);
	d->objs = ft_calloc(sizeof(t_objs), d->nbr_objs);
	if (!d->objs)
		return (print_err("Error: Malloc failed.", d), 1);
	i = -1;
	while (d->raw[++i])
	{
		tmp = ft_split(d->raw[i], ' ');
		define_obj(d, tmp, i);
	}
	return (0);
}

int	read_file(t_data *d, char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	process_file (d, fd);
	close(fd);
	if (d->nbr_objs == 0)
		print_err("Error: Empty Map.", d);
	printf("Map init successfully.\n");
	return (0);
}
