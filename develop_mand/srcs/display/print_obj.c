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

// int	num_binary_digits(int n)
// {
// 	int	count;

// 	count = 0;
// 	while (n != 0)
// 	{
// 		n /= 2;
// 		count++;
// 	}
// 	return (count);
// }

void	print_sphere(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("sp ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.radius * 2, fd);
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
	ft_putnbr_fd(obj.radius * 2, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.height, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

// C 0,150,-100 0.0,0.0,1.0 90
// A 0.0 255,255,255
// # A 0.4 255,255,255
// L 0,50,0 0.0 255,255,255
// # L 0,50,0 0.8 255,255,255
// cy 100,100,200 -1.0,0.0,0.0 50 100 255,0,255
// cy -100,100,200 0.0,0.0,0.0 100 100 0,155,255
// # cy -100,100,200 1,-1,0 100 100 0,155,255
// pl 0,0,0 0.0,1.0,0.0 255,255,255
// pl 0,0,500 0.0,0.0,-1.0 255,255,255
void	print_cone(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("co ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	print_vector(obj.dir, fd, 1);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.radius * 2, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.height, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}
