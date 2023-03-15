// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/11/13 16:13:24 by ykuo              #+#    #+#             */
// /*   Updated: 2022/11/13 16:13:25 by ykuo             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minirt.h"

// int	hextoint(char *str, char *base)
// {
// 	int	count[4];
// 	int	ans;

// 	count[0] = 0;
// 	ans = 0;
// 	while (str[count[0]])
// 	{
// 		count[1] = 0;
// 		while (base[count[1]])
// 		{
// 			if (str[count[0]] == base[count[1]])
// 			{
// 				ans = ans * 16 + count[1];
// 				break ;
// 			}
// 			count[1] += 1;
// 		}
// 		if (base [count[1]] == '\0')
// 			break ;
// 		count[0] += 1;
// 	}
// 	return (ans);
// }

// int	map_setup(t_data *d, int x, int y)
// {
// 	char	**tmp;

// 	tmp = ft_split(d->map[xy_to_x(d, x, y)], ',');
// 	init_vector(d->map_3d[xy_to_x(d, x, y)], x * d->line_length,
// 		y * d->line_length, ft_atoi(tmp[0]) * -d->height);
// 	free (tmp[0]);
// 	if (tmp[1])
// 	{
// 		d->map_3d[xy_to_x(d, x, y)]->c = hextoint(tmp[1] + 2, BASE);
// 		free (tmp[1]);
// 	}
// 	else
// 		d->map_3d[xy_to_x(d, x, y)]->c = COLOR_WHITE;
// 	free (tmp);
// 	return (0);
// }

// int	init_map3d(t_data *d)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < d->map_h)
// 	{
// 		x = -1;
// 		while (++x < d->map_w)
// 		{
// 			init_vector(d->map_2d[xy_to_x(d, x, y)], 0, 0, 0);
// 			map_setup(d, x, y);
// 		}
// 	}
// 	return (0);
// }

// int	init_map(t_data *d)
// {
// 	int	y;

// 	y = -1;
// 	d->map_2d
// 		= (t_vector **) malloc((d->map_w * d->map_h) * sizeof(t_vector *));
// 	if (!d->map_2d)
// 		print_err("Error: Memory allocate failed", d);
// 	ft_bzero(d->map_2d, sizeof(t_vector *));
// 	while (++y < (d->map_h * d->map_w))
// 		d->map_2d[y] = (t_vector *) ft_malloc(d, sizeof(t_vector));
// 	y = -1;
// 	d->map_3d
// 		= (t_vector **) malloc((d->map_w * d->map_h) * sizeof(t_vector *));
// 	if (!d->map_3d)
// 		print_err("Error: Memory allocate failed", d);
// 	ft_bzero(d->map_3d, sizeof(t_vector *));
// 	while (++y < (d->map_h * d->map_w))
// 		d->map_3d[y] = (t_vector *) ft_malloc(d, sizeof(t_vector));
// 	init_map3d(d);
// 	return (0);
// }

// int	init_var(t_data *d)
// {
// 	int	i;
// 	int	max;

// 	init_map(d);
// 	d->u = (t_vector *) ft_malloc(d, sizeof(t_vector));
// 	init_vector(d->u, 1, 0, 0);
// 	d->v = (t_vector *) ft_malloc(d, sizeof(t_vector));
// 	init_vector(d->v, 0, 0, 1);
// 	d->rot = (t_vector *) ft_malloc(d, sizeof(t_vector));
// 	init_vector(d->rot, 21, 16, -3);
// 	d->center = (t_vector *) ft_malloc(d, sizeof(t_vector));
// 	init_vector(d->center, 150, 0, 0);
// 	d->line_length = (WIDTH / d->map_w) * 0.5;
// 	i = -1;
// 	max = 1;
// 	while (d->map[++i])
// 		max = ft_max(max, ft_abs(ft_atoi(d->map[i])));
// 	d->height = (HEIGHT / 3) / max;
// 	d->height2 = d->height / 2;
// 	d->projection = 1;
// 	return (0);
// }
