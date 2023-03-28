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
