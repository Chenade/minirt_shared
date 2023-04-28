/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:41:16 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/28 02:41:17 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	num_binary_digits(int n)
// {
// 	int	count;

// 	count = 0;
// 	while (n != 0)
// 	{
// 		n /= 2;
// 		count++;
// 	}
// 	return (count);
// }

void	print_bits_64(unsigned long long int n)
{
	int	i;

	i = 64;
	while (i > 0)
	{
		printf("%llu", (n & 1));
		n = n >> 1;
		i--;
		if (i == 12 || i == 1)
			printf(" ");
	}
	printf("\n");
}

#include <stdlib.h>
#include <string.h>

int get_digits(double num) {
	int digits = 0;
	while (num >= 1.0) {
		num /= 10.0;
		digits++;
	}
	return digits;
}

void reverse_str(char *str) {
	int len = strlen(str);
	for (int i = 0; i < len / 2; i++) {
		char temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

char *ft_putdouble_fd2(double d, int fd) {
	char	*str;
	int		is_neg;
	int		integer_part;
	double	fraction_part;
	int		digits_before_decimal;
	int		digits_after_decimal = 6;

	is_neg = 0;
	if (d < 0)
	{
		is_neg = 1;
		d *= -1;
	}
	integer_part = (int)d;
	fraction_part = d - integer_part;
	digits_before_decimal = get_digits(integer_part);
	digits_after_decimal = 6;
	str = malloc((is_neg + digits_before_decimal + digits_after_decimal + 2) * sizeof(char));

	// Convert integer part to string
	int i = 0;
	while (integer_part > 0) {
		str[i++] = (integer_part % 10) + '0';
		integer_part /= 10;
	}
	if (i == 0) {
		str[i++] = '0';
	}
	if (is_neg)
		str[i++] = '-';
	str[i + is_neg] = '\0';
	reverse_str(str);

	// Add decimal point and fractional part
	str[i++] = '.';
	for (int j = 0; j < digits_after_decimal; j++) {
		fraction_part *= 10.0;
		int digit = (int)fraction_part;
		str[i++] = digit + '0';
		fraction_part -= digit;
	}
	str[i] = '\0';

	// Print to file descriptor
	write(fd, str, strlen(str));
	write(fd, "\n", 1);
	return str;
}

// void	ft_putdouble_fd2(double d, int fd)
// {
// 	double			dec;
// 	unsigned long long int		n;
// 	unsigned long long int		b_mask;
// 	unsigned long long int		e;
// 	unsigned long long int		raw_b;
// 	unsigned long long int		raw_dec;

// 	b_mask = (unsigned long long int)2047 << 52;
// 	print_bits_64(b_mask);
// 	(void)fd;
// 	if (d > 0)
// 	{
// 		n = d;
// 		dec = d - n;
// 	}
// 	else
// 	{
// 		n = d * -1;
// 		dec = d + n;
// 	}
// 	raw_b = *(unsigned long long int *)&d;
// 	raw_dec = *(unsigned long long int *)&dec;
// 	e = (b_mask & raw_dec);// >> 52;// & b_mask;
// 	printf("d : %f\n", d);
// 	printf("n : %llu\n", n);
// 	printf("dec : %f\n", dec);
// 	printf("raw d : %llu\n", raw_b);
// 	print_bits_64(raw_b);
// 	printf("e : %llu\n", e);
// 	print_bits_64(e);
// 	printf("raw dec : %llu\n", raw_dec);
// 	printf("---------------------------------------------------\n");
// }

void	print_sphere(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("sp ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.radius * 2, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_plane(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("pl ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	print_vector(obj.dir, fd, 1);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_cylinder(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("cy ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	print_vector(obj.dir, fd, 1);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.radius * 2, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.height, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}

void	print_cone(t_data *d, int index, int fd)
{
	t_objs	obj;

	obj = d->objs[index];
	ft_putstr_fd("co ", fd);
	print_vector(obj.pos, fd, 0);
	ft_putstr_fd(" ", fd);
	print_vector(obj.dir, fd, 1);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.radius * 2, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(obj.height, fd);
	ft_putstr_fd(" ", fd);
	print_color(obj.color, fd);
	ft_putstr_fd("\n", fd);
}
