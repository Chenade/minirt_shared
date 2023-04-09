/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:22:40 by znogueir          #+#    #+#             */
/*   Updated: 2023/03/26 22:22:41 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_vector(t_vector *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (0);
}

void	get_cur_vec(t_data *d, int x, int y)
{
	d->cur_p.dir.x = (-WIDTH / 2 + x);
	d->cur_p.dir.y = (HEIGHT / 2 - y);
	d->cur_p.dir.z = (d->cam_len);
	d->cur_p.dir = normalize_vect(d->cur_p.dir);
	// d->cur_p.dir = normalize_vect(vec_sum(d->cur_p.dir, normalize_vect(d->cam->dir)));
}
