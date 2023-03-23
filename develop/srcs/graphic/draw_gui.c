#include "minirt.h"

int	draw_gui(t_data *d)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 10;
	mlx = d->mlx_ptr;
	win = d->win_ptr;
	mlx_string_put(mlx, win, 35, y += 20, COLOR_TEXT, "How to Use");
	return (0);
}
