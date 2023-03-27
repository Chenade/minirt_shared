#include "minirt.h"

void	print_sphere(t_data *d, int index, int fd)
{
	
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("sp ", fd);
	print_vector(obj.cord, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.diameter, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_plane(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("pl ", fd);
	print_vector(obj.cord, fd);
	ft_putstr_fd(" ", fd);
	print_vector(obj.orientation, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_cylinder(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("cy ", fd);
	print_vector(obj.cord, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.diameter, fd);
	ft_putstr_fd(" ", fd);
	print_vector(obj.orientation, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}
