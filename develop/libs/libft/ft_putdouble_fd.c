/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:27:05 by ykuo              #+#    #+#             */
/*   Updated: 2023/04/13 14:27:18 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putdouble_fd(double d, int fd)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(d);
	tmp = str;
	str = ft_strjoin(str, ".");
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, "0");
	free(tmp);
	ft_putstr_fd(str, fd);
	return (str);
}
