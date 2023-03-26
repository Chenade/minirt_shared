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
	(void) d;
	(void) keysym;
	printf("%s: %d\n", __func__, d->index);
	return (0);
}

int	key_plane(t_data *d, int keysym)
{
	(void) d;
	(void) keysym;
	printf("%s: %d\n", __func__, d->index);
	return (0);
}

int	key_cylinder(t_data *d, int keysym)
{
	(void) d;
	(void) keysym;
	printf("%s: %d\n", __func__, d->index);
	return (0);
}

int	key_camera(t_data *d, int keysym)
{
	(void) d;
	(void) keysym;
	printf("%s: %d\n", __func__, d->index);
	return (0);
}

int	key_light(t_data *d, int keysym)
{
	(void) d;
	(void) keysym;
	printf("%s: %d\n", __func__, d->index);
	return (0);
}
