#include "cub3D.h"

void	check_screen_size(t_mlx *all)
{
	int	width;
	int	height;

	if ((*all).win)
	{
		mlx_get_screen_size(all, &width, &height);
		if ((*all).win && (int)(*all).r_xy[0] > width)
			(*all).r_xy[0] = width;
		if ((*all).win && (int)(*all).r_xy[1] > height)
			(*all).r_xy[1] = height;
	}
}

void	start_mlx(t_mlx *all)
{
	int	i;

	start_mlx_texture(all);
	(*all).r_xy[0] = 0;
	(*all).r_xy[1] = 0;
	i = 3;
	while (i--)
	{
		(*all).f_rgb[i] = 0;
		(*all).c_rgb[i] = 0;
	}
	(*all).does_paste_r = 0;
	(*all).does_paste_f = 0;
	(*all).does_paste_c = 0;
	(*all).nb_lines = 0;
	while (i < 7)
		(*all).nswe_s[i++] = 0;
	(*all).map = NULL;
	(*all).len_str_max = 0;
	(*all).player = 0;
	(*all).line = NULL;
	(*all).free_line = NULL;
	start_move_sprite_wall(all);
}

void	start_move_sprite_wall(t_mlx *all)
{
	(*all).pl_h_bonus = (float)PL_HEIGHT;
	(*all).k_view_hight = (SIZE_BLOCK - (*all).pl_h_bonus) / SIZE_BLOCK;
	(*all).dist_wall = NULL;
	(*all).sprite_data = NULL;
	(*all).move.a = 0;
	(*all).move.w = 0;
	(*all).move.d = 0;
	(*all).move.s = 0;
	(*all).move.arrow_l = 0;
	(*all).move.arrow_r = 0;
	(*all).nb_sprite = 0;
	(*all).nb_sprite3 = 0;
	(*all).collect_spr = 0;
	(*all).move.map = 0;
}

void	start_mlx_texture(t_mlx *all)
{
	int	i;

	(*all).mlx = NULL;
	(*all).win = NULL;
	(*all).mlx = mlx_init();
	if (!(*all).mlx)
	{
		write(1, "Error\nmlx_init error.\n", 23);
		exit (1);
	}
	i = -1;
	while (++i < 7)
	{
		(*all).texture_nswe_s[i].img = NULL;
		(*all).texture_nswe_s[i].addr = NULL;
	}
	(*all).frame.img = NULL;
}

int	exit_clean(t_mlx *all, int i, int ii)
{
	while (++i < 7)
		if ((*all).texture_nswe_s[i].img)
			mlx_destroy_image((*all).mlx, ((*all).texture_nswe_s[i].img));
	if ((*all).frame.img)
		mlx_destroy_image((*all).mlx, (*all).frame.img);
	exit_clean2(all, i, ii);
	if ((*all).map)
		free((*all).map);
	if ((*all).sprite_data)
		free((*all).sprite_data);
	if ((*all).win)
		mlx_destroy_window(all->mlx, all->win);
	exit (1);
}
