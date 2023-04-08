#include "minirt.h"

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vector	vec_sum(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vector	vec_fact(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vector	vec_scale(t_vector v, double scaler)
{
	t_vector	w;

	w.x = v.x * scaler;
	w.y = v.y * scaler;
	w.z = v.z * scaler;
	return (w);
}
