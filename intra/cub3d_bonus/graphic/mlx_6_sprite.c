#include "../cub3D.h"

void	sprite_wall_zero(t_mlx *all)
{
	int	i;

	i = -1;
	while (++i <= (*all).nb_sprite)
	{
		(*all).sprite_data[i].x = 0;
		(*all).sprite_data[i].y = 0;
		(*all).sprite_data[i].dist = 0;
		(*all).sprite_data[i].i = -1;
	}
	i = -1;
	while (++i <= (int)(*all).r_xy[0])
		(*all).dist_wall[i] = 0;
}

void	sprite_fill_struct(t_mlx *all, float xp, float yp)
{
	int		i;
	double	angle_view;

	i = check_new_sprite(all, (int)xp, (int)yp);
	if ((*all).sprite_data[i].x == 0)
	{
		(*all).sprite_data[i].x = (int)xp;
		(*all).sprite_data[i].y = (int)yp;
		(*all).sprite_data[i].spr = (*all).map[(int)xp][(int)yp];
		(*all).sprite_data[i].dist = sqrt(pow((int)xp + 0.5 - (*all).x_pl, 2)
				+ pow((int)yp + 0.5 - (*all).y_pl, 2));
		angle_view = asin(fabs(floor(xp) + 0.5 - (*all).x_pl)
				/ (*all).sprite_data[i].dist);
		(*all).sprite_data[i].i = sprite_i(all, xp, yp, angle_view);
	}
}

int	check_new_sprite(t_mlx *all, int xp, int yp)
{
	int	i;

	i = 0;
	while ((*all).sprite_data[i].x)
	{
		if ((*all).sprite_data[i].x == (int)xp
			&& (*all).sprite_data[i].y == (int)yp)
			return (i);
		++i;
	}
	return (i);
}

float	sprite_i(t_mlx *all, float xp, float yp, double angle_view)
{
	float	i;
	float	ang_l;
	float	step_ang;

	if (((int)xp + 0.5 - (*all).x_pl) > 0 && ((int)yp + 0.5 - (*all).y_pl) > 0)
		angle_view = M_PI - angle_view;
	if (((int)xp + 0.5 - (*all).x_pl) < 0 && ((int)yp + 0.5 - (*all).y_pl) > 0)
		angle_view = angle_view + M_PI;
	if (((int)xp + 0.5 - (*all).x_pl) < 0 && ((int)yp + 0.5 - (*all).y_pl) < 0)
		angle_view = -angle_view;
	if (!((int)xp + 0.5 - (*all).x_pl) && ((int)yp + 0.5 - (*all).y_pl) > 0)
		angle_view = M_PI;
	if (!((int)xp + 0.5 - (*all).x_pl) && ((int)yp + 0.5 - (*all).y_pl) < 0)
		angle_view = 0;
	if (((int)xp + 0.5 - (*all).x_pl) > 0 && !((int)yp + 0.5 - (*all).y_pl))
		angle_view = M_PI_2;
	if (((int)xp + 0.5 - (*all).x_pl) < 0 && !((int)yp + 0.5 - (*all).y_pl))
		angle_view = 3 * M_PI_2;
	ang_l = (*all).start_pi + (FOV * M_PI / 180) / 2;
	step_ang = (FOV * M_PI / 180) / (*all).r_xy[0];
	i = (ang_l - angle_view) / step_ang;
	if (ang_l - angle_view + (FOV * M_PI / 180) / 2 >= 2 * M_PI)
		i = (ang_l - angle_view - 2 * M_PI) / step_ang;
	return (i);
}

t_spr	*sprite_sort(t_mlx *all, int i, int j, int k)
{
	t_spr		*sprite_data_sort;

	while ((*all).sprite_data[i].x)
		++i;
	sprite_data_sort = (t_spr *)malloc((i + 1) * sizeof(t_spr));
	if (!sprite_data_sort)
		write(1, "Error\nmalloc error.\n", 21);
	if (!sprite_data_sort)
		exit_clean(all, -1, 0);
	sprite_data_sort[i].x = 0;
	while (++k < i)
	{
		i = -1;
		j = k;
		while ((*all).sprite_data[++i].x)
			if ((*all).sprite_data[j].dist < (*all).sprite_data[i].dist)
				j = i;
		sprite_data_sort[k].x = (*all).sprite_data[j].x;
		sprite_data_sort[k].y = (*all).sprite_data[j].y;
		sprite_data_sort[k].dist = (*all).sprite_data[j].dist;
		sprite_data_sort[k].i = (*all).sprite_data[j].i;
		sprite_data_sort[k].spr = (*all).sprite_data[j].spr;
		(*all).sprite_data[j].dist = 0;
	}
	return (sprite_data_sort);
}
