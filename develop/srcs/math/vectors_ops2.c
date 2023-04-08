#include "minirt.h"

double	get_norm(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

double	get_vec_norm(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.x * v2.z - v1.z * v2.x;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	normalize_vect(t_vector v)
{
	double		norm;
	t_vector	w;

	norm = get_norm(v.x, v.y, v.z);
	w.x = v.x / norm;
	w.y = v.y / norm;
	w.z = v.z / norm;
	return (w);
}
