/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_menus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:52:04 by znogueir          #+#    #+#             */
/*   Updated: 2023/04/24 00:52:06 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_move_menu(t_data *d, char *n_type, int type)
{
	int		y;

	y = HEIGHT - GUI_HEIGHT + 40;
	mlx_putstr(d, 178, HEIGHT - GUI_HEIGHT + 20, n_type);
	mlx_putstr(d, 20, y + 20, "Move :");
	mlx_putstr(d, 64, y += 20, "Along   (Right/Left) : Left / Right Arrows");
	mlx_putstr_r(d, 100, y, "X");
	mlx_putstr(d, 64, y += 20, "Along   (Up/Down) : Y / H");
	mlx_putstr_g(d, 100, y, "Y");
	mlx_putstr(d, 64, y += 20, \
	"Along   (Forwards/Backwards) : Up / Down Arrows");
	mlx_putstr_b(d, 100, y, "Z");
	if (type == SP || type == CY || type == CO)
	{
		y = HEIGHT - GUI_HEIGHT + 110;
		mlx_putstr(d, 20 + 180 * (type == CY || type == CO), y += 20, \
		"Resize :");
		mlx_putstr(d, 20 + 180 * (type == CY || type == CO), y += 20, \
		"Diameter (+/-) : J / K");
	}
}

void	print_complete_menu(t_data *d, char *n_type, int type)
{
	int		y;

	y = HEIGHT - GUI_HEIGHT + 110;
	print_move_menu(d, n_type, type);
	mlx_putstr(d, 20, y + 20, "Rotate :");
	mlx_putstr(d, 74, y += 20, "Around   : W / S");
	mlx_putstr_r(d, 117, y, "X");
	mlx_putstr(d, 74, y += 20, "Around   : D / A");
	mlx_putstr_g(d, 117, y, "Y");
	mlx_putstr(d, 74, y += 20, "Around   : E / Q");
	mlx_putstr_b(d, 117, y, "Z");
	if (type == CY || type == CO)
		mlx_putstr(d, 200, y, "Height (+/-) : U / I");
}

void	print_cam_menu(t_data *d)
{
	int		y;

	y = HEIGHT - GUI_HEIGHT + 45;
	mlx_putstr(d, 175, HEIGHT - GUI_HEIGHT + 20, "Camera");
	mlx_putstr(d, 30, y += 20, "Look Around : W A S D");
	mlx_putstr(d, 30, y += 20, "Tilt right and left : E / Q");
	mlx_putstr(d, 30, y += 20, "Turn Around : R");
	mlx_putstr(d, 30, y += 40, "Move Around : Arrow keys");
	mlx_putstr(d, 30, y += 20, "Go Up and Down : Y / H");
}

void	print_menu(t_data *d)
{
	int	type;

	type = d->objs[d->index].type;
	if (type == CAM)
		print_cam_menu(d);
	else if (type == LIGHT)
		print_move_menu(d, "Light", type);
	else if (type == AMB)
		mlx_putstr(d, 160, HEIGHT - GUI_HEIGHT + 20, "Ambient light");
	else if (type == SP)
		print_move_menu(d, "Sphere", type);
	else if (type == PL)
		print_complete_menu(d, "Plane", type);
	else if (type == CY)
		print_complete_menu(d, "Cylinder", type);
	else if (type == CO)
		print_complete_menu(d, "Cone", type);
}
