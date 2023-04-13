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

int	map_check_sphere(t_data *d, char **line, int index)
{
	double	diameter;

	if (ft_array_len(line) != 4)
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	diameter = ft_strtod(line[2]);
	if (diameter > 1000)
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	d->objs[index].radius = diameter / 2;
	if (set_color(&d->objs[index].color, line[3]))
		return (print_err("Error\n: Invalid Map: Sphere", d), 1);
	d->objs[index].type = SP;
	d->objs[index].collision_func = hit_sphere;
	d->objs[index].shadow_func = sphere_shadow;
	d->objs[index].keyboard_func = key_sphere;
	d->objs[index].gui_func = gui_sphere;
	d->objs[index].print_func = print_sphere;
	d->objs[index].math.radius_2 = \
	d->objs[index].radius * d->objs[index].radius;
	return (0);
}

int	map_check_plane(t_data *d, char **line, int index)
{
	if (ft_array_len(line) != 4)
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	if (set_dir(&d->objs[index].dir, line[2]))
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	d->objs[index].dir = normalize_vect(d->objs[index].dir);
	if (set_color(&d->objs[index].color, line[3]))
		return (print_err("Error\n: Invalid Map: Plane", d), 1);
	d->objs[index].type = PL;
	d->objs[index].collision_func = hit_plane;
	d->objs[index].shadow_func = plane_shadow;
	d->objs[index].keyboard_func = key_plane;
	d->objs[index].gui_func = gui_plane;
	d->objs[index].print_func = print_plane;
	return (0);
}

void	init_math(t_objs *obj)
{
	obj->math.radius_2 = obj->radius * obj->radius;
	obj->math.a = obj->dir.x;
	obj->math.b = obj->dir.y;
	obj->math.c = obj->dir.z;
	obj->math.xm = obj->pos.x;
	obj->math.ym = obj->pos.y;
	obj->math.zm = obj->pos.z;
	obj->math.a_2 = obj->math.a * obj->math.a;
	obj->math.b_2 = obj->math.b * obj->math.b;
	obj->math.c_2 = obj->math.c * obj->math.c;
	obj->math.xm_2 = obj->math.xm * obj->math.xm;
	obj->math.ym_2 = obj->math.ym * obj->math.ym;
	obj->math.zm_2 = obj->math.zm * obj->math.zm;
}

void	init_func(t_objs *objs)
{
	objs->type = CYL;
	objs->collision_func = hit_cylinder;
	objs->shadow_func = cylinder_shadow;
	objs->keyboard_func = key_cylinder;
	objs->gui_func = gui_cylinder;
	objs->print_func = print_cylinder;
}

int	map_check_cylinder(t_data *d, char **line, int index)
{
	double	diameter;
	double	height;

	if (ft_array_len(line) != 6)
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	diameter = ft_strtod(line[3]);
	if (diameter > 1000)
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	d->objs[index].radius = diameter / 2;
	height = ft_strtod(line[4]);
	d->objs[index].height = height;
	if (set_dir(&d->objs[index].dir, line[2]))
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	d->objs[index].dir = normalize_vect(d->objs[index].dir);
	if (set_color(&d->objs[index].color, line[5]))
		return (print_err("Error\n: Invalid Map: Cylinder", d), 1);
	init_func(&d->objs[index]);
	d->objs[index].cap_1 = vec_sum(d->objs[index].pos, \
	vec_scale(d->objs[index].dir, d->objs[index].height / 2));
	d->objs[index].cap_2 = vec_sum(d->objs[index].pos, \
	vec_scale(d->objs[index].dir, -d->objs[index].height / 2));
	init_math(&d->objs[index]);
	return (0);
}
