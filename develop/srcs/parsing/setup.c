#include "minirt.h"

int	set_vector(t_vector *v, char *str)
{
	char **arr;

	arr = ft_split(str, ',');
	if (!arr || !arr[0] || !arr[1] || !arr[2])
		return (1);
	v->x = ft_strtod(arr[0]);
	v->y = ft_strtod(arr[1]);
	v->z = ft_strtod(arr[2]);
	return (0);
}

int	set_orientation(t_vector *v, char *str)
{
	char **arr;

	arr = ft_split(str, ',');
	if (!arr || !arr[0] || !arr[1] || !arr[2])
		return (1);
	v->x = ft_strtod(arr[0]);
	v->y = ft_strtod(arr[1]);
	v->z = ft_strtod(arr[2]);
	return (0);
}

int	set_color(t_color *c, char *str)
{
	char **arr;

	arr = ft_split(str, ',');
	if (!arr || !arr[0] || !arr[1] || !arr[2])
		return (1);
	if (ft_atoi(arr[0]) < 0 || ft_atoi(arr[0]) > 255
		|| ft_atoi(arr[1]) < 0 || ft_atoi(arr[1]) > 255
		|| ft_atoi(arr[2]) < 0 || ft_atoi(arr[2]) > 255)
		return (1);
	c->r = ft_atoi(arr[0]);
	c->g = ft_atoi(arr[1]);
	c->b = ft_atoi(arr[2]);
	return (0);
}
