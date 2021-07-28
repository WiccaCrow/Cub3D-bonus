#include "../cub3D.h"

/*****************************************
*	1.4.6. render_next_frame		    *
******************************************
*	Check move next step. Run drow functions.
*
*	self functions:
*	1.3.4.1.1. exit_clean
*		./map/fil_map_part2.c
*	1.4.6.1. move_adws
*		./graphic/mlx_2_raycasting.c
*	1.4.6.2. drow_frame_3d
*		./graphic/mlx_2_raycasting.c
*/

int	render_next_frame(t_mlx *all)
{
	mlx_do_sync((*all).mlx);
	if ((*all).move.a == 1)
		move_adws(all, 1, M_PI_2, 0);
	if ((*all).move.d == 1)
		move_adws(all, 1, -M_PI_2, 0);
	if ((*all).move.w == 1)
		move_adws(all, 1, 0, 0);
	if ((*all).move.s == 1)
		move_adws(all, -1, 0, 0);
	if ((*all).move.arrow_l == 1)
		(*all).move_round += ROUND;
	if ((*all).move.arrow_r == 1)
		(*all).move_round -= ROUND;
	(*all).x_pl += (*all).move_x;
	(*all).y_pl += (*all).move_y;
	(*all).move_x = 0;
	(*all).move_y = 0;
	(*all).frame.img
		= mlx_new_image((*all).mlx, (*all).r_xy[0], (*all).r_xy[1]);
	if (!(*all).frame.img)
		write(1, "Error\nmlx error.\n", 18);
	if (!(*all).frame.img)
		exit_clean(all, -1, 0);
	drow_frame_3d(all, 0);
	return (0);
}

/*****************************************
*		1.4.3. key_press			     *
******************************************
*	functions:
*	1.3.4.1.1. exit_clean
*/

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
		if (keycode == KEY_ESC)
			exit_clean (all, -1, 0);
	}
	return (keycode);
}

/*****************************************
*		1.4.3. key_release			     *
******************************************
*/

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
	}	
	return (keycode);
}

/*****************************************
*	1.4. ft_mlx_functions			    *
******************************************
*	Drow frames. Refresh screen.
*
*	self functions:
*	1.3.4.1.1. exit_clean
*		./map/fil_map_part2.c
*	1.4.1. sprite_wall_zero
*		./graphic/mlx_6_sprite.c
*	1.4.2. find_x_y_player
*		./graphic/mlx_2_raycasting.c
*	1.4.3. key_press
*	1.4.4. key_release
*	1.3.4.1.1. exit_clean
*	1.4.6. render_next_frame
*/

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
		mlx_hook((*al).win, X11_EVENTS_EXIT, 1L << 17, exit_clean, al);
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
