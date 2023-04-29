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
#include <stdlib.h>
#include <string.h>

int	get_digits(double num)
{
	int	digits;

	digits = 0;
	while (num >= 1.0)
	{
		num /= 10.0;
		digits++;
	}
	return (digits);
}

void	reverse_str(char *str)
{
	int		i;
	int		len;
	char	temp;

	i = -1;
	len = strlen(str);
	while (++i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

int	convert_int_to_str(int integer_part, char *str, int is_neg)
{
	int	i;

	i = 0;
	while (integer_part > 0)
	{
		str[i++] = (integer_part % 10) + '0';
		integer_part /= 10;
	}
	if (i == 0)
		str[i++] = '0';
	if (is_neg)
		str[i++] = '-';
	str[i] = '\0';
	reverse_str(str);
	return (i);
}

int	convert_fra_to_str(double fraction_part, char *str, int i, \
	int digits_after_decimal)
{
	int	j;
	int	digit;

	j = 0;
	str[i++] = '.';
	while (j < digits_after_decimal)
	{
		fraction_part *= 10.0;
		digit = (int) fraction_part;
		str[i++] = digit + '0';
		fraction_part -= digit;
		j += 1;
	}
	str[i] = '\0';
	return (i);
}

char	*ft_putdouble_fd(double d, int fd)
{
	char	*str;
	int		is_neg;
	int		integer_part;
	double	fraction_part;
	int		digits_before_decimal;

	is_neg = 0;
	if (d < 0)
	{
		is_neg = 1;
		d *= -1;
	}
	integer_part = (int) d;
	fraction_part = d - integer_part;
	digits_before_decimal = get_digits(integer_part);
	str = malloc((is_neg + digits_before_decimal + 6 + 2) \
		* sizeof(char));
	convert_fra_to_str(fraction_part, str, \
	convert_int_to_str(integer_part, str, is_neg), 6);
	write(fd, str, strlen(str));
	return (str);
}
