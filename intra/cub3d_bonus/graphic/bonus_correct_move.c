#include "../cub3D.h"

void	bonus_correct_move(t_mlx *all, int flag_down)
{
	if (flag_down == 1)
		(*all).pl_h_bonus = PL_HEIGHT_DOWN;
	if (flag_down == 0)
		(*all).pl_h_bonus = PL_HEIGHT;
	(*all).k_view_hight = (SIZE_BLOCK - (*all).pl_h_bonus) / SIZE_BLOCK;
	if (flag_down == 2)
	{
		(*all).pl_h_bonus = PL_HEIGHT_UP;
		(*all).k_view_hight = (SIZE_BLOCK - (*all).pl_h_bonus) / SIZE_BLOCK;
	}
}

void	bonus_collect_sprite(t_mlx *all)
{
	char	*s_nb;

	s_nb = NULL;
	if ((*all).collect_spr < 2147483646)
	{
		mlx_string_put((*all).mlx, (*all).win, (*all).r_xy[0]
			/ 2, 16, 0x00FF2566, "your books: ");
		s_nb = ft_itoa((*all).collect_spr);
		mlx_string_put((*all).mlx, (*all).win, (*all).r_xy[0]
			/ 2 + 12 * 8, 16, 0x00FF0066, s_nb);
		free(s_nb);	
	}
	else
		mlx_string_put((*all).mlx, (*all).win, (*all).r_xy[0]
			/ 2, 16, 0x00FF2566, "books: 2147483646 (max)");
		mlx_string_put((*all).mlx, (*all).win, (*all).r_xy[0]
			/ 2, 32, 0x00FF2566, "all  books:");
		s_nb = ft_itoa((*all).nb_sprite3);
		mlx_string_put((*all).mlx, (*all).win, (*all).r_xy[0]
			/ 2 + 12 * 8, 32, 0x00FF0066, s_nb);
		free(s_nb);	
}

void	bonus_render_next_frame_start(t_mlx *all)
{
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
}

void	bonus_volume(void)
{
	// system("afplay --volume 1 2.wav &");
	// system("afplay --volume 2 5.wav &");
	system("aplay 2.wav &");
	// system("aplay 5.wav &");

}
