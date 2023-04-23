/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_put_rect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 01:00:41 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/24 01:00:43 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_line(t_data *d, int x, int y, int l)
{
	int	i;

	i = -1;
	while (i++ < l)
		img_pix_put(&d->menu_back, x + i, y, d->rec_col);
}

void	draw_column(t_data *d, int x, int y, int l)
{
	int	i;

	i = -1;
	while (i++ < l)
		img_pix_put(&d->menu_back, x, y + i, d->rec_col);
}

void	put_rect(t_data *d, t_vector p, int w, int h)
{
	draw_line(d, p.x, p.y, w);
	draw_column(d, p.x, p.y, h);
	draw_line(d, p.x, p.y + h, w);
	draw_column(d, p.x + w, p.y, h);
}
