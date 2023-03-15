#include "libft.h"

double ft_strtod(char *str)
{
	double res;
	double sign;
	double power;

	res = 0;
	sign = 1;
	power = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		power *= 10;
	}
	return (res * sign / power);
}