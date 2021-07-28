#include "../cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	drow_wall_floor_ceil(t_mlx *all, float height,
	float pl_height, float x)
{
	int	i;
	int	color_c;
	int	color;

	i = 0;
	while (i <= pl_height && i < (int)(*all).r_xy[1] / 2)
	{
		color = color_wall(all, height, i, (*all).k_view_hight);
		my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 + i++, color);
	}
	color = create_trgb(0, (*all).f_rgb[0], (*all).f_rgb[1], (*all).f_rgb[2]);
	while ((*all).r_xy[1] / 2 + i < (*all).r_xy[1] && (i > pl_height))
		my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 + i++, color);
	i = 1;
	while (i <= (height - pl_height) && ((*all).r_xy[1] / 2 - i))
	{
		color = color_wall(all, height, -i, (*all).k_view_hight);
		my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 - i++, color);
	}
	color_c = create_trgb(0, (*all).c_rgb[0], (*all).c_rgb[1], (*all).c_rgb[2]);
	while ((*all).r_xy[1] / 2 - i)
		my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 - i++, color_c);
	if (i > (height - pl_height))
		color = color_c;
	my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 - i, color);
}

double	intersections_v1(t_mlx *all, double ang_pi, double ang_cor)
{
	double	xp;
	double	yp;
	double	a;

	xp = (*all).x_pl;
	yp = (*all).y_pl;
	if (ang_pi >= M_PI_2 && ang_pi <= 3 * M_PI_2)
		a = ceil(yp) - yp;
	else
		a = yp - floor(yp) + 0.00001;
	if (intersections_v2(all, &xp, &yp, a))
		return (-1);
	if (ang_pi == M_PI_2 || ang_pi == 3 * M_PI_2)
		(*all).ray_length = fabs(yp - (*all).y_pl);
	else
		(*all).ray_length = fabs(yp - (*all).y_pl) / cos(ang_cor);
	(*all).x_w = xp;
	(*all).y_w = yp;
	return ((*all).ray_length);
}

int	intersections_v2(t_mlx *all, double *xp, double *yp, double a)
{
	double	b;
	double	ang_pi;

	ang_pi = (*all).start_pi + (FOV * M_PI / 180) / 2;
	ang_pi -= (*all).i * (FOV * M_PI / 180) / (*all).r_xy[0];
	while (!ft_strchr("14", (*all).map[(int)*xp][(int)*yp]))
	{
		if (ft_strchr("23", (*all).map[(int)*xp][(int)*yp]))
			sprite_fill_struct(all, *xp, *yp);
		b = a * tan(ang_correct(ang_pi));
		if ((ang_pi >= M_PI && ang_pi <= 2 * M_PI)
			|| (ang_pi >= -M_PI && ang_pi <= 0))
			b = -b;
		*xp += b;
		if (!(ang_pi >= M_PI_2 && ang_pi <= 3 * M_PI_2))
			a = -a;
		*yp += a;
		if (*xp >= (*all).nb_lines || *yp >= (*all).len_str_max
			|| *xp < 0 || *yp < 0)
			return (-1);
		a = 1;
	}
	return (0);
}
