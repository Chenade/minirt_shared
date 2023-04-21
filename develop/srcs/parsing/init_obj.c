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

// void	init_math(t_objs *obj)
// {
// 	obj->math.radius_2 = obj->radius * obj->radius;
// 	obj->math.a = obj->dir.x;
// 	obj->math.b = obj->dir.y;
// 	obj->math.c = obj->dir.z;
// 	obj->math.xm = obj->pos.x;
// 	obj->math.ym = obj->pos.y;
// 	obj->math.zm = obj->pos.z;
// 	obj->math.a_2 = obj->math.a * obj->math.a;
// 	obj->math.b_2 = obj->math.b * obj->math.b;
// 	obj->math.c_2 = obj->math.c * obj->math.c;
// 	obj->math.xm_2 = obj->math.xm * obj->math.xm;
// 	obj->math.ym_2 = obj->math.ym * obj->math.ym;
// 	obj->math.zm_2 = obj->math.zm * obj->math.zm;
// }

// void	update_math(t_objs *obj, t_data *d, t_vector p)
// {
// 	obj->math.i = d->cur_p.dir.x;
// 	obj->math.j = d->cur_p.dir.y;
// 	obj->math.k = d->cur_p.dir.z;
// 	obj->math.xp = p.x;
// 	obj->math.yp = p.y;
// 	obj->math.zp = p.z;
// 	obj->math.i_2 = obj->math.i * obj->math.i;
// 	obj->math.j_2 = obj->math.j * obj->math.j;
// 	obj->math.k_2 = obj->math.k * obj->math.k;
// 	obj->math.xp_2 = obj->math.xp * obj->math.xp;
// 	obj->math.yp_2 = obj->math.yp * obj->math.yp;
// 	obj->math.zp_2 = obj->math.zp * obj->math.zp;
// }

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
