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

/*
calculating the axes of the camera :

- z axis = cam->dir;
- y axis : needs to be perpendicular to z, but with a positive y component;
- x axis : needs to be perpendicular to z and y, with a y component == 0;

for x, we're gonna do the cross product of the cam->dir and the y axis of
the world;

for y, the cross product of the new x axis and the cam->dir;

we normalize everything of course and that's it;

so we have :

cam->dir_x = normalize_vect(cross_product(cam->dir, vector(0, 1, 0)));
cam->dir_y = normalize_vect(cross_product(cam->dir_y, cam->dir));
*/

// DEPRECATED
// void	get_init_angles(t_objs *obj)
// {
// 	t_vector	dir;

// 	dir = normalize_vect(obj->dir);
// 	// Compute the yaw angle (rotation around the Y-axis)
// 	obj->angle_y = atan2(dir.x, dir.z);

// 	// Compute the pitch angle (rotation around the X-axis)
// 	obj->angle_x = asin(-dir.y / \
// 	sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));

// 	// Set the roll angle (rotation around the Z-axis) to zero
// 	obj->angle_z = 0.0;

// 	printf("%f, %f, %f\n", obj->angle_x, obj->angle_y, obj->angle_z);
// 	// printf("%f, %f, %f\n", obj->angle_x, obj->angle_y, obj->angle_z);
// }

void	print_vec(t_vector v)
{
	printf("x : %f, y : %f, z : %f\n", v.x, v.y, v.z);
}

int		compare_vecs(t_vector v, t_vector w)
{
	if (v.x != w.x)
		return (0);
	if (v.y != w.y)
		return (0);
	return (v.z == w.z);
}

void	get_cam_axes(t_objs *cam)
{
	t_vector	world_y;

	world_y = vector(0, 1, 0);
	if (compare_vecs(cam->dir, world_y))
		cam->dir_x = vector(1, 0, 0);
	else if (compare_vecs(cam->dir, vector(0, -1, 0)))
		cam->dir_x = vector(-1, 0, 0);
	else
		cam->dir_x = normalize_vect(cross_product(world_y, cam->dir));
	cam->dir_y = normalize_vect(cross_product(cam->dir_x, cam->dir));
	printf("cam axes : \n");
	print_vec(cam->dir_x);
	print_vec(cam->dir_y);
	print_vec(cam->dir);
}

int	map_check_cam(t_data *d, char **line, int index)
{
	double	fov;

	if (d->nbr_camera != 0)
		return (1);
	d->nbr_camera += 1;
	if (ft_array_len(line) != 4)
		return (1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (1);
	if (set_dir(&d->objs[index].dir, line[2]))
		return (1);
	if (d->objs[index].dir.x == 0 && d->objs[index].dir.y == 0
		&& d->objs[index].dir.z == 0)
		return (1);
	fov = ft_strtod(line[3]);
	if (fov < 0 || fov > 180)
		return (1);
	d->fov = fov;
	d->objs[index].type = DEF;
	get_cam_axes(&d->objs[index]);
	d->objs[index].keyboard_func = key_camera;
	d->objs[index].gui_func = gui_camera;
	d->objs[index].print_func = print_camera;
	d->cam = &d->objs[index];
	return (0);
}

int	map_check_ambient(t_data *d, char **line, int index)
{
	double	intensity;

	if (d->nbr_ambient != 0)
		return (1);
	d->nbr_ambient += 1;
	if (ft_array_len(line) != 3)
		return (1);
	intensity = ft_strtod(line[1]);
	if (intensity < 0 || intensity > 1)
		return (1);
	d->objs[index].intensity = intensity;
	if (set_color(&d->objs[index].color, line[2]))
		return (1);
	d->objs[index].type = DEF;
	d->objs[index].color = d->objs[index].color;
	d->objs[index].intensity = d->objs[index].intensity;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_ambient;
	d->objs[index].print_func = print_ambient;
	d->ambient = &d->objs[index];
	return (0);
}

int	map_check_light(t_data *d, char **line, int index)
{
	double	intensity;

	if (d->nbr_light != 0)
		return (1);
	d->nbr_light += 1;
	if (ft_array_len(line) != 4)
		return (1);
	if (set_vector(&d->objs[index].pos, line[1]))
		return (1);
	intensity = ft_strtod(line[2]);
	if (intensity < 0 || intensity > 1)
		return (1);
	d->objs[index].intensity = intensity;
	if (set_color(&d->objs[index].color, line[3]))
		return (1);
	d->objs[index].type = DEF;
	d->objs[index].radius = 3;
	d->objs[index].collision_func = hit_light;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_light;
	d->objs[index].print_func = print_light;
	d->light = &d->objs[index];
	d->objs[index].math.radius_2 = \
	d->objs[index].radius * d->objs[index].radius;
	return (0);
}
