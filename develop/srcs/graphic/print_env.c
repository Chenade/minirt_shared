#include "minirt.h"

void	print_vector(t_vector v, int fd)
{
	ft_putnbr_fd(v.x, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(v.y, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(v.z, fd);
}

void	print_color(t_color c, int fd)
{
	ft_putnbr_fd(c.r, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(c.g, fd);
	ft_putstr_fd(",", fd);
	ft_putnbr_fd(c.b, fd);
}

void	print_camera(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("C ", fd);
	print_vector(obj.cord, fd);
	ft_putstr_fd(" ", fd);
	print_vector(obj.orientation, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(d->fov, fd);
	ft_putstr_fd("\n", fd);
}

void	print_light(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("L ", fd);
	print_vector(obj.cord, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.ratio, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_ambient(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("A ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}
