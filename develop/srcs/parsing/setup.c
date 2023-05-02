/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:32:12 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/17 19:32:13 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_overflow(char *str)
{
	int		i;
	int		passed_dot;
	int		count;
	char	*trimed;

	i = -1;
	passed_dot = 0;
	count = 0;
	trimed = ft_strtrim(str, "0");
	while (trimed[++i])
	{
		if (trimed[i] == '.' && passed_dot == 1)
			return (free(trimed), 1);
		if (trimed[i] == '.' && passed_dot == 0)
		{
			count = i;
			passed_dot = 1;
		}
	}
	if (i - count > 15 || count > 20)
		return (free(trimed), 1);
	return (free(trimed), 0);
}

int	set_vector(t_vector *v, char *str)
{
	int		i;
	char	**arr;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != ',' && \
			str[i] != '.')
			return (1);
	arr = ft_split(str, ',');
	if (!arr || !arr[0] || !arr[1] || !arr[2])
		return (1);
	if (check_overflow(arr[0]) || check_overflow(arr[1]) || \
		check_overflow(arr[2]))
		return (1);
	v->x = ft_strtod(arr[0]);
	v->y = ft_strtod(arr[1]);
	v->z = ft_strtod(arr[2]);
	ft_free_array(arr);
	return (0);
}

int	set_dir(t_vector *v, char *str)
{
	int		i;
	char	**arr;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != ',' && \
			str[i] != '.')
			return (1);
	arr = ft_split(str, ',');
	if (!arr || !arr[0] || !arr[1] || !arr[2])
		return (1);
	if (check_overflow(arr[0]) || check_overflow(arr[1]) || \
		check_overflow(arr[2]))
		return (1);
	v->x = ft_strtod(arr[0]);
	v->y = ft_strtod(arr[1]);
	v->z = ft_strtod(arr[2]);
	if (v->x == 0 && v->y == 0 && v->z == 0)
		return (1);
	ft_free_array(arr);
	*v = normalize_vect(*v);
	return (0);
}

int	set_color(t_color *c, char *str)
{
	char	**arr;

	arr = ft_split(str, ',');
	if (!arr || !arr[0] || !arr[1] || !arr[2])
		return (1);
	if (ft_atoi(arr[0]) < 0 || ft_atoi(arr[0]) > 255
		|| ft_atoi(arr[1]) < 0 || ft_atoi(arr[1]) > 255
		|| ft_atoi(arr[2]) < 0 || ft_atoi(arr[2]) > 255)
		return (1);
	c->r = ft_atoi(arr[0]);
	c->g = ft_atoi(arr[1]);
	c->b = ft_atoi(arr[2]);
	ft_free_array(arr);
	return (0);
}
