/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:13:03 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:13:06 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_sphere(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	printf("%s: %d, %d\n", __func__, d->index, i);
	return (i);
}

int	key_plane(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = (i || ft_orientation(&d->objs[d->index], keysym));
	printf("%s: %d, %d\n", __func__, d->index, i);
	return (i);
}

int	key_cylinder(t_data *d, int keysym)
{
	int	i;

	i = ft_move(&d->objs[d->index], keysym);
	i = ft_orientation(&d->objs[d->index], keysym);
	printf("%s: %d, %d\n", __func__, d->index, i);
	return (i);
}
