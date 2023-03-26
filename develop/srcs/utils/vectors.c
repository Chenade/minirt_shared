#include "minirt.h"

int	init_vector(t_vector *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (0);
}

double	get_norm(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

double	cross_product(t_vector v1, t_vector v2)
{
	return ((v1.y * v2.z - v1.z * v2.y) - (v1.x * v2.z - v1.z * v2.x) \
	+ (v1.x * v2.y - v1.y * v2.x));
}
