#include "../cub3D.h"

int	render_next_frame(t_mlx *all)
{
	mlx_do_sync((*all).mlx);
	bonus_render_next_frame_start(all);
	if (!(*all).frame.img)
	{
		write(1, "Error\nmlx error.\n", 18);
		exit_clean(all, -1, 0);
	}
	if ((*all).move.map)
		drow_map(all);
	else
		drow_frame_3d(all, 0);
	return (0);
}

int	key_press(int keycode, t_mlx *all)
{
	if (all)
	{
		if (keycode == KEY_LEFT_A)
			(*all).move.a = 1;
		if (keycode == KEY_UP_W)
			(*all).move.w = 1;
		if (keycode == KEY_RIGHT_D)
			(*all).move.d = 1;
		if (keycode == KEY_DOWN_S)
			(*all).move.s = 1;
		if (keycode == KEY_LEFT_ARROW)
			(*all).move.arrow_l = 1;
		if (keycode == KEY_RIGHT_ARROW)
			(*all).move.arrow_r = 1;
		if (keycode == KEY_DOWN_ARROW)
			bonus_correct_move(all, 1);
		if (keycode == KEY_UP_ARROW)
			bonus_correct_move(all, 2);
		if (keycode == KEY_ESC)
			exit_clean (all, -1, 0);
		if (keycode == KEY_M)
			(*all).move.map = 1;
	}
	return (keycode);
}

int	key_release(int keycode, t_mlx *all)
{
	if (all)
	{
		if (keycode == KEY_LEFT_A)
			(*all).move.a = 0;
		if (keycode == KEY_UP_W)
			(*all).move.w = 0;
		if (keycode == KEY_RIGHT_D)
			(*all).move.d = 0;
		if (keycode == KEY_DOWN_S)
			(*all).move.s = 0;
		if (keycode == KEY_LEFT_ARROW)
			(*all).move.arrow_l = 0;
		if (keycode == KEY_RIGHT_ARROW)
			(*all).move.arrow_r = 0;
		if (keycode == KEY_DOWN_ARROW || keycode == KEY_UP_ARROW)
			bonus_correct_move(all, 0);
		if (keycode == KEY_M)
			(*all).move.map = 0;
	}	
	return (keycode);
}

void	ft_mlx_functions(t_mlx *al)
{
	(*al).sprite_data = (t_spr *)malloc(((*al).nb_sprite + 1) * sizeof(t_spr));
	(*al).dist_wall = (float *)malloc(((*al).r_xy[0] + 1) * sizeof(float));
	if (!(*al).sprite_data || !(*al).dist_wall)
	{
		write(1, "Error\nmalloc error.\n", 21);
		exit_clean(al, -1, 0);
	}
	sprite_wall_zero(al);
	find_x_y_player(al, 0, 0);
	if ((*al).win)
	{
		mlx_hook((*al).win, X11_EVENTS_KEYPRESS, 1L << 0, key_press, al);
		mlx_hook((*al).win, X11_EVENTS_KEYREL, 1L << 1, key_release, al);
		mlx_hook((*al).win, X11_EVENTS_EXIT, 0, exit_clean, al);
		mlx_loop_hook((*al).mlx, render_next_frame, al);
		mlx_loop((*al).mlx);
	}
	else
		render_next_frame(al);
	free((*al).sprite_data);
	free((*al).dist_wall);
	(*al).sprite_data = NULL;
	(*al).dist_wall = NULL;
}
