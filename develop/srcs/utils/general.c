/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:13:44 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:13:45 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_icons(t_data *d)
{
	if (d->cam_icon.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->cam_icon.mlx_img);
	if (d->light_icon.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->light_icon.mlx_img);
	if (d->amb_icon.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->amb_icon.mlx_img);
	if (d->sp_icon.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->sp_icon.mlx_img);
	if (d->cy_icon.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->cy_icon.mlx_img);
}

void	free_data(t_data *d)
{
	int	i;

	if (d->win_ptr)
		mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	if (d->img.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->img.mlx_img);
	if (d->menu_back.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->menu_back.mlx_img);
	free_icons(d);
	if (d->mlx_ptr)
		mlx_destroy_display(d->mlx_ptr);
	free(d->mlx_ptr);
	free(d->objs);
	i = -1;
	while (d->raw[++i])
		free(d->raw[i]);
	free(d->raw);
	i = -1;
}

void	print_err(const char *err_msg, t_data *d)
{
	ft_printf("%s\n", err_msg);
	free_data(d);
	exit(EXIT_FAILURE);
}

int	check_filename(const char *name, const char *ext)
{
	int	x;

	x = ft_strlen(name) - ft_strlen(ext);
	if (ft_strncmp(name + x, ext, ft_strlen(ext)))
		return (0);
	return (1);
}
