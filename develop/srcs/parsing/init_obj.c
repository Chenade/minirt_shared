/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:46:15 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/21 20:46:16 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_sp(t_data *d, int index)
{
	d->objs[index].type = SP;
	d->objs[index].collision_func = hit_sphere;
	d->objs[index].shadow_func = sphere_shadow;
	d->objs[index].keyboard_func = key_sphere;
	d->objs[index].gui_func = gui_sphere;
	d->objs[index].print_func = print_sphere;
	d->objs[index].math.radius_2 = \
	d->objs[index].radius * d->objs[index].radius;
}

void	init_pl(t_data *d, int index)
{
	d->objs[index].type = PL;
	d->objs[index].collision_func = hit_plane;
	d->objs[index].shadow_func = plane_shadow;
	d->objs[index].keyboard_func = key_plane;
	d->objs[index].gui_func = gui_plane;
	d->objs[index].print_func = print_plane;
}

void	init_cyl(t_data *d, int index)
{
	d->objs[index].type = CYL;
	d->objs[index].collision_func = hit_cylinder;
	d->objs[index].shadow_func = cylinder_shadow;
	d->objs[index].keyboard_func = key_cylinder;
	d->objs[index].gui_func = gui_cylinder;
	d->objs[index].print_func = print_cylinder;
	d->objs[index].dir = normalize_vect(d->objs[index].dir);
	d->objs[index].cap_1 = vec_sum(d->objs[index].pos, \
	vec_scale(d->objs[index].dir, d->objs[index].height / 2));
	d->objs[index].cap_2 = vec_sum(d->objs[index].pos, \
	vec_scale(d->objs[index].dir, -d->objs[index].height / 2));
	d->objs[index].math.radius_2 = \
	d->objs[index].radius * d->objs[index].radius;
}
