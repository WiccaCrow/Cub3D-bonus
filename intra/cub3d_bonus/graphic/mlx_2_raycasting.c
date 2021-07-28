#include "../cub3D.h"

double	ang_correct(double angle)
{
	if (angle > M_PI_2 && angle < M_PI)
		angle = angle - M_PI;
	if (angle >= M_PI && angle < 3 * M_PI_2)
		angle = angle - M_PI;
	if (angle > 3 * M_PI_2 && angle <= 2 * M_PI)
		angle = angle - 2 * M_PI;
	if (angle == M_PI_2 && angle == 3 * M_PI_2)
		angle = 0;
	return (fabs(angle));
}

void	check_move_stop(t_mlx *all, float *move_x, float *move_y)
{
	int		x;
	int		y;
	float	i;

//	i = SPEED / (float)(*all).r_xy[0];
	i = 0;
	while (i <= 4)
	{
		x = (int)((*all).x_pl + i * *move_x);
		y = (int)((*all).y_pl + i * *move_y);
		if (ft_strchr("12", (*all).map[x][y]))
		{
			*move_x = 0;
			*move_y = 0;
			break ;
		}
		i += SPEED / (float)(*all).r_xy[0];
	}
	if ((*all).map[x][y] == '3')
	{
		if ((*all).collect_spr < 2147483646)
			(*all).collect_spr++;
		(*all).map[x][y] = '0';
	}
}

void	move_adws(t_mlx *all, int	ws, double ang_adws, float	move_y)
{
	int		sign;
	double	angle;
	double	ang_mv;
	float	move_x;

	ang_mv = (*all).start_pi + ang_adws;
	angle = ang_correct(ang_mv);
	sign = -1;
	if ((ang_mv >= 0 && ang_mv <= M_PI)
		|| (ang_mv >= 2 * M_PI && ang_mv <= 3 * M_PI))
		sign = 1;
	move_x = ws * sign * SPEED * fabs(sin(angle));
	sign = -1;
	if (ang_mv >= M_PI_2 && ang_mv <= 3 * M_PI_2)
		sign = 1;
	if (ang_mv == -M_PI_2)
		sign = 1;
	move_y = ws * sign * SPEED * cos(angle);
	check_move_stop(all, &move_x, &move_y);
	(*all).move_x += move_x;
	(*all).move_y += move_y;
}

void	drow_frame_3d(t_mlx *al, double	angle)
{
	(*al).frame.addr = mlx_get_data_addr((*al).frame.img,
			&(*al).frame.b_p_p, &(*al).frame.line_l, &(*al).frame.endian);
	if ((*al).player == 'N')
		(*al).start_pi = 3 * M_PI_2;
	if ((*al).player == 'E')
		(*al).start_pi = M_PI;
	if ((*al).player == 'W')
		(*al).start_pi = 0;
	if ((*al).player == 'S')
		(*al).start_pi = M_PI_2;
	(*al).start_pi += (*al).move_round;
	while ((*al).start_pi >= 2 * M_PI)
		(*al).start_pi -= 2 * M_PI;
	while ((*al).start_pi < 0)
		(*al).start_pi += 2 * M_PI;
	angle = (*al).start_pi + (FOV * M_PI / 180) / 2;
	find_wall(al, angle);
	drow_map_mini(al);
	if ((*al).win)
		mlx_put_image_to_window((*al).mlx, (*al).win, (*al).frame.img, 0, 0);
	else
		save_bmp(al);
	mlx_destroy_image((*al).mlx, (*al).frame.img);
	if ((*al).win)
		bonus_collect_sprite(al);
	(*al).frame.img = NULL;
}

void	find_x_y_player(t_mlx *all, float x, float y)
{
	while (x < (*all).nb_lines)
	{
		y = 0;
		while (x < (*all).nb_lines && y <= (*all).len_str_max)
		{
			if ((*all).map[(int)x][(int)y] == (*all).player)
			{
				(*all).x_pl = x + 0.5;
				(*all).y_pl = y + 0.5;
				return ;
			}
			++y;
		}
		++x;
	}
}
