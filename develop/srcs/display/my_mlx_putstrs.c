/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_putstrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:52:12 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/24 00:52:14 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_putstr(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, WHITE, str);
}

void	mlx_putstr_r(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, RED, str);
}

void	mlx_putstr_g(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, GREEN, str);
}

void	mlx_putstr_b(t_data *d, int x, int y, char *str)
{
	mlx_string_put(d->mlx_ptr, d->win_ptr, x, y, BLUE, str);
}
