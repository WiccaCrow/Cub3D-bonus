#include "../cub3D.h"

double	intersections_h1(t_mlx *all, double ang_pi)
{
	double	xp;
	double	yp;
	double	b;

	xp = (*all).x_pl;
	yp = (*all).y_pl;
	if ((ang_pi >= 0 && ang_pi <= M_PI)
		|| (ang_pi >= 2 * M_PI && ang_pi <= 3 * M_PI))
		b = ceil(xp) - xp;
	else
		b = xp - floor(xp) + 0.00001;
	if (intersections_h2(all, &xp, &yp, b))
		return ((*all).ray_length);
	return (intersections_h4(all, ang_pi, xp, yp));
}

int	intersections_h2(t_mlx *all, double *xp, double *yp, double b)
{
	double	a;
	double	ang_pi;

	ang_pi = (*all).start_pi + (FOV * M_PI / 180) / 2;
	ang_pi -= (*all).i * (FOV * M_PI / 180) / (*all).r_xy[0];
	while (!ft_strchr("14", (*all).map[(int)*xp][(int)*yp]))
	{
		if (ft_strchr("23", (*all).map[(int)*xp][(int)*yp]))
			sprite_fill_struct(all, *xp, *yp);
		if (ang_correct(ang_pi) == 0)
			a = 0;
		else
			a = b / tan(ang_correct(ang_pi));
		if ((ang_pi >= M_PI && ang_pi <= 2 * M_PI)
			|| (ang_pi >= -M_PI && ang_pi <= 0))
			b = -b;
		*xp += b;
		if (!(ang_pi >= M_PI_2 && ang_pi <= 3 * M_PI_2))
			a = -a;
		*yp += a;
		if (intersections_h3_wall_color(all, xp, yp, ang_pi))
			return (1);
		b = 1;
	}
	return (0);
}

int	intersections_h3_wall_color(t_mlx *all, double *xp, double *yp,
	double ang_pi)
{
	if (*xp >= (*all).nb_lines || *yp >= (*all).len_str_max || *xp < 0
		|| *yp < 0)
	{
		if (!(ang_pi >= M_PI_2 && ang_pi <= 3 * M_PI_2))
			(*all).wall_color = 'W';
		else
			(*all).wall_color = 'E';
		return (1);
	}
	return (0);
}

double	intersections_h4(t_mlx *all, double ang_pi, double xp, double yp)
{
	double	ray_vertical;

	ray_vertical = (*all).ray_length;
	if (ang_pi && (ang_pi == M_PI || ang_pi == 2. * M_PI))
		(*all).ray_length = fabs(xp - (*all).x_pl);
	else
		(*all).ray_length = fabs((xp - (*all).x_pl) / sin(ang_correct(ang_pi)));
	if ((*all).ray_length > ray_vertical && ray_vertical != -1)
	{
		(*all).ray_length = ray_vertical;
		if (ang_pi >= M_PI_2 && ang_pi <= 3 * M_PI_2)
			(*all).wall_color = 'E';
		else
			(*all).wall_color = 'W';
	}
	else
	{
		(*all).x_w = xp;
		(*all).y_w = yp;
	}
	return ((*all).ray_length);
}

void	find_wall(t_mlx *all, double ang)
{
	float			distance_to_plane;
	float			wall_h;

	distance_to_plane = (*all).r_xy[0] / 2 / tan(FOV * M_PI / 360);
	(*all).i = 0;
	while ((*all).i < (*all).r_xy[0])
	{
		if ((ang >= 0 && ang <= M_PI) || (ang >= 2 * M_PI && ang <= 3 * M_PI))
			(*all).wall_color = 'S';
		else
			(*all).wall_color = 'N';
		(*all).ray_length = intersections_v1(all, ang, ang_correct(ang));
		(*all).ray_length = intersections_h1(all, ang);
		(*all).dist_wall[(*all).i] = (*all).ray_length;
		wall_h = distance_to_plane / (*all).ray_length
			/ fabs(cos(ang_correct(ang - (*all).start_pi)));
		if ((*all).map[(int)(*all).x_pl][(int)(*all).y_pl] != '4')
			drow_wall_floor_ceil(all, wall_h, wall_h * (*all).pl_h_bonus
				/ (float)SIZE_BLOCK, (*all).i);
		ang -= (FOV * M_PI / 180) / (*all).r_xy[0];
		(*all).i++;
	}
	sprite_drow1(all, distance_to_plane, 0, -1);
	sprite_wall_zero(all);
}
