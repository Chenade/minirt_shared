/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:41:16 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/28 02:41:17 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("sp ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.radius, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_plane(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("pl ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	print_vector(obj.dir, fd, 1);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_cylinder(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("cy ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	print_vector(obj.dir, fd, 1);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.radius, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.height, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}
