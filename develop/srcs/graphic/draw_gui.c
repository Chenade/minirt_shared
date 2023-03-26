/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:29:41 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/23 20:29:42 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	draw_gui(t_data *d)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 10;
	mlx = d->mlx_ptr;
	win = d->win_ptr;
	mlx_string_put(mlx, win, 35, y += 20, COLOR_TEXT, "How to Use");
	return (0);
}
