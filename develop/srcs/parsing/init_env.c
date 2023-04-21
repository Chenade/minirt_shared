/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:39:11 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/21 20:39:14 by znogueir         ###   ########.fr       */
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

void	get_cam_axes(t_objs *cam)
{
	t_vector	world_y;

	world_y = vector(0, 1, 0);
	cam->dir = normalize_vect(cam->dir);
	if (compare_vecs(cam->dir, world_y) || \
	compare_vecs(cam->dir, vector(0, -1, 0)))
		cam->dir_x = vector(1, 0, 0);
	else
		cam->dir_x = normalize_vect(cross_product(world_y, cam->dir));
	// printf("prev cam axes : \n");
	// print_vec(cam->dir_x);
	// print_vec(cam->dir);
	cam->dir_y = normalize_vect(cross_product(cam->dir, cam->dir_x));
	// printf("new cam axes : \n");
	// print_vec(cam->dir_x);
	// print_vec(cam->dir_y);
	// print_vec(cam->dir);
}

void	init_cam(t_data *d, int index)
{
	d->objs[index].type = DEF;
	get_cam_axes(&d->objs[index]);
	d->objs[index].keyboard_func = key_camera;
	d->objs[index].gui_func = gui_camera;
	d->objs[index].print_func = print_camera;
	d->cam = &d->objs[index];
}

void	init_ambient(t_data *d, int index)
{
	d->objs[index].type = DEF;
	d->objs[index].color = d->objs[index].color;
	d->objs[index].intensity = d->objs[index].intensity;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_ambient;
	d->objs[index].print_func = print_ambient;
	d->ambient = &d->objs[index];
}

void	init_light(t_data *d, int index)
{
	d->objs[index].type = DEF;
	d->objs[index].radius = 3;
	d->objs[index].collision_func = hit_light;
	d->objs[index].keyboard_func = key_light;
	d->objs[index].gui_func = gui_light;
	d->objs[index].print_func = print_light;
	d->light = &d->objs[index];
	d->objs[index].math.radius_2 = \
	d->objs[index].radius * d->objs[index].radius;
}
