#include "./cub3D.h"

/*****************************************
*		1.3.8. check_screen_size         *
******************************************
*	Check the screen size.
*/

void	check_screen_size(t_mlx *all)
{
	if (!(*all).argv2)
	{
		if ((int)(*all).r_xy[0] > 2560)
			(*all).r_xy[0] = 2560;
		if ((int)(*all).r_xy[1] > 1440)
			(*all).r_xy[1] = 1440;
	}
}

/*****************************************
*	1.1.    start_mlx         			 *
******************************************
*	Start all variables and pointers.
*
*	functions:
*	1.1.1. start_mlx_texture
*	1.1.2. start_move_sprite_wall
*/

void	start_mlx(t_mlx *all)
{
	int	i;

	start_mlx_texture(all);
	(*all).r_xy[0] = 0;
	(*all).r_xy[1] = 0;
	i = 3;
	while (i--)
	{
		(*all).f_rgb[i] = -1;
		(*all).c_rgb[i] = -1;
	}
	(*all).does_paste_r = 0;
	(*all).does_paste_f = 0;
	(*all).does_paste_c = 0;
	(*all).nb_lines = 0;
	while (i < 6)
		(*all).nswe_s[i++] = 0;
	(*all).map = NULL;
	(*all).len_str_max = 0;
	(*all).player = 0;
	(*all).line = NULL;
	(*all).free_line = NULL;
	start_move_sprite_wall(all);
}

/*****************************************
*	1.1.2. start_move_sprite_wall		 *
******************************************
*/	

void	start_move_sprite_wall(t_mlx *all)
{
	(*all).k_view_hight = (SIZE_BLOCK - (float)PL_HEIGHT) / SIZE_BLOCK;
	(*all).dist_wall = NULL;
	(*all).sprite_data = NULL;
	(*all).move.a = 0;
	(*all).move.w = 0;
	(*all).move.d = 0;
	(*all).move.s = 0;
	(*all).move.arrow_l = 0;
	(*all).move.arrow_r = 0;
}

/*****************************************
*		1.1.1. start_mlx_texture		 *
******************************************
*/

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
	while (++i < 5)
	{
		(*all).texture_nswe_s[i].img = NULL;
		(*all).texture_nswe_s[i].addr = NULL;
	}
	(*all).frame.img = NULL;
}

/*****************************************
*		1.3.4.1.1. exit_clean   	     *
******************************************
*	Exit program. Clean exit.
*/

int	exit_clean(t_mlx *all, int i, int ii)
{
	while (++i < 5)
		if ((*all).texture_nswe_s[i].img)
			mlx_destroy_image((*all).mlx, ((*all).texture_nswe_s[i].img));
	if ((*all).frame.img)
		mlx_destroy_image((*all).mlx, (*all).frame.img);
	if ((*all).free_line && (*all).free_line == (*all).line)
		(*all).free_line = NULL;
	if ((*all).line)
		free((*all).line);
	(*all).line = NULL;
	if ((*all).free_line)
		free((*all).free_line);
	(*all).free_line = NULL;
	if ((*all).dist_wall)
		free((*all).dist_wall);
	(*all).dist_wall = NULL;
	while (ii < (*all).nb_lines + 1 && ((*all).map && (*all).map[i]))
		free((*all).map[ii++]);
	if ((*all).map)
		free((*all).map);
	if ((*all).sprite_data)
		free((*all).sprite_data);
	if ((*all).win)
		mlx_destroy_window(all->mlx, all->win);
	exit (1);
}
