
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	int	c;
}	t_vector;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_objs
{
	char		*type;
	void		*checker;
	t_vector	cord;
	t_vector	orientation;
	t_color		color;
	double		fov;
	double		ratio;
	double		diameter;
	double		height;
} t_objs;


typedef struct s_data
{
	void		*win_ptr;
	void		*mlx_ptr;
	t_img		img;


	char		*buf;
	int			size;
	int			w;
	int			h;

	int			nbr_objs;
	char		**raw;
	struct s_objs	*objs;
}	t_data;


// typedef struct s_data
// {
// 	void		*win_ptr;
// 	void		*mlx_ptr;
// 	t_img		img;


// 	char		*buf;
// 	int			size;
// 	t_vector	*u;
// 	t_vector	*v;
// 	int			w;
// 	int			h;

// 	int			map_h;
// 	int			map_w;
// 	char		**map;
// 	t_vector	**map_3d;
// 	t_vector	**map_2d;
// 	int			line_length;
// 	int			height;
// 	int			height2;
// 	t_vector	*center;
// 	t_vector	*rot;
// 	int			projection;

// 	int			nbr_objs;
// 	char		**raw;
// 	struct s_objs	*objs;
// }	t_data;
