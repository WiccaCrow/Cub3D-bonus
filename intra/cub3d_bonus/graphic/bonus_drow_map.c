#include "../cub3D.h"

/*
* COLOR_SPRITE = 0x00125618
* COLOR_WALLS = 0x00909090
*/

void	drow_map(t_mlx *all)
{
	int	x;
	int	y;

	ft_scale(all);
	(*all).frame.addr = mlx_get_data_addr((*all).frame.img,
			&(*all).frame.b_p_p, &(*all).frame.line_l, &(*all).frame.endian);
	x = 0;
	while (x < (*all).nb_lines)
	{
		y = 0;
		while (y < (*all).len_str_max)
		{
			if (ft_strchr("1234", (*all).map[x][y]))
				ft_mlx_one_bloke(all, x, y, (*all).map[x][y]);
			++y;
		}
		++x;
	}
	ft_mlx_one_bloke(all, (*all).x_pl, (*all).y_pl, 'p');
	mlx_put_image_to_window((*all).mlx, (*all).win, (*all).frame.img, 0, 0);
	mlx_destroy_image((*all).mlx, (*all).frame.img);
	(*all).frame.img = NULL;
}

void	ft_scale(t_mlx *all)
{
	float	scale_correct_x;
	float	scale_correct_y;

	(*all).scale = SIZE_BLOCK;
	if ((unsigned int)((*all).nb_lines * SIZE_BLOCK) >= (*all).r_xy[1]
		|| (unsigned int)((*all).len_str_max * SIZE_BLOCK) >= (*all).r_xy[0])
	{
		scale_correct_x = (*all).r_xy[1] / (unsigned int)(*all).nb_lines;
		scale_correct_y = (*all).r_xy[0] / (unsigned int)(*all).len_str_max;
		if (scale_correct_x > scale_correct_y)
			(*all).scale = scale_correct_y;
		else
			(*all).scale = scale_correct_x;
		if ((int)(*all).scale % 2)
			(*all).scale = (*all).scale - 1;
		return ;
	}
	(*all).scale = SIZE_BLOCK;
}

void	ft_mlx_one_bloke(t_mlx *all, int x, int y, char c)
{
	int	i;
	int	j;
	int	scale;
	int	color;

	color = 0x00909090;
	scale = (*all).scale;
	if (c == '2')
		color = 0x00125618;
	if (c == '3')
		color = 0x00565618;
	if (c == '4')
		color = 0x00789090;
	if (c == 'p')
		color = 0x0000FFFF;
	i = 0;
	j = 0;
	while (i < scale)
	{
		j = -1;
		while (++j < scale)
			my_mlx_pix_put(&(*all).frame, y * (*all).scale + i,
				x * (*all).scale + j, color);
		i++;
	}
}

void	drow_map_mini(t_mlx *all)
{
	int	x;
	int	y;

	ft_scale(all);
	x = 0;
	while (x < (*all).nb_lines)
	{
		y = 0;
		while (y < (*all).len_str_max)
		{
			if (x > (*all).x_pl - 6 && x < (*all).x_pl + 6
				&& y > (*all).y_pl - 6 && y < (*all).y_pl + 6)
			{
				if (ft_strchr("1234", (*all).map[x][y]))
					ft_mlx_one_bloke(all, x - (*all).x_pl + 7,
						y - (*all).y_pl + 7, (*all).map[x][y]);
			}
			++y;
		}
		++x;
	}
	ft_mlx_one_bloke(all, 6, 6, 'p');
}
