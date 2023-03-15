/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:13:37 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:13:38 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

long int	find_size(char file_name[])
{
	FILE		*fp;
	long int	res;

	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		ft_printf("File Not Found!\n");
		return (-1);
	}
	fseek(fp, 0L, SEEK_END);
	res = ftell(fp);
	fclose(fp);
	return (res);
}

void	print_img_data(t_img *i)
{
	ft_printf("bit per pixel %d\n", i->bpp);
	ft_printf("endian %d\n", i->endian);
	ft_printf("line_len %d\n", i->line_len);
}

int	print_info(char *name)
{
	long	size;

	size = find_size(name);
	ft_printf("size of file %ld bytes\n", size);
	return (size);
}

// int	print_map(t_data *d, t_vector **map)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < d->map_h)
// 	{
// 		x = -1;
// 		while (++x < d->map_w)
// 		{
// 			ft_printf("(%d, %d, %d)  ", map[xy_to_x(d, x, y)]->x,
// 				map[xy_to_x(d, x, y)]->y, map[xy_to_x(d, x, y)]->z);
// 		}
// 		ft_printf("\n");
// 	}
// 	ft_printf("\n");
// 	return (0);
// }

void	*ft_malloc(t_data *d, size_t size)
{
	void	*ptr;

	ptr = (void *) malloc (size);
	if (!(ptr))
	{
		print_err("Error: Memory allocate failed", d);
		return (NULL);
	}
	ft_bzero(ptr, size);
	return (ptr);
}
