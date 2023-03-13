## Parsing
- Your program must take as a first argument a scene description file with the .rt extension
- check all the requirment fo each type
  - A
  - C
  - L
  - sp
  - pl
  - cy

struct	t_data
{
	[some mlx stuff];
	struct objs[];
}

struct	vector3
{
	float	x;
	float	y;
	float	z;
}

struct t_color
{
	int	r;
	int	g;
	int	b;
}

struct objs
{
	char	*type;
	vector3	cord;
	t_color	color;
	vextor3	3d_normailized;
	double	ratio;
	double	diameter;
	double	height;
}

## Raycasting
