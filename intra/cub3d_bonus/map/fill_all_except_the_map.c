#include "../cub3D.h"

/*****************************************
* 1.3.5.1. check_no_so_we_ea_sspace      *
******************************************
*	Check valid symbols befor map.
*/

void	check_no_so_we_ea_sspace(t_mlx *all)
{
	if (!(((*all).line[(*all).ii + 2] == ' ' && (((*all).line[(*all).ii] == 'N'
						&& (*all).line[(*all).ii + 1] == 'O')
					|| ((*all).line[(*all).ii] == 'W'
						&& (*all).line[(*all).ii + 1] == 'E')
					|| ((*all).line[(*all).ii] == 'E'
						&& (*all).line[(*all).ii + 1] == 'A')))
			|| ((*all).line[(*all).ii] == 'S'
				&& ft_strchr("O234", (*all).line[(*all).ii + 1]))))
	{
		write(1, "Error\nNot valid symbols befor map.\n", 36);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
}

/*****************************************
*		1.3.5. paste_no_so_we_ea_s       *
******************************************
*	Paste parameters NO SO WE EA S.
*
*	functions:
*	1.3.5.1. check_no_so_we_ea_sspace
*	1.3.5.2. texture1
*		./graphic/mlx_5_texture.c
*/

void	paste_no_so_we_ea_s(t_mlx *all, int i)
{
	(*all).ii = i;
	check_no_so_we_ea_sspace(all);
	i = 2;
	while ((*all).line[(*all).ii + i] == ' ')
		++i;
	if ((*all).line[(*all).ii] == 'N' && (*all).line[(*all).ii + 1] == 'O')
		texture1(all, &(*all).line[(*all).ii + i], 0, ".xpm");
	if ((*all).line[(*all).ii] == 'S' && (*all).line[(*all).ii + 1] == 'O')
		texture1(all, &(*all).line[(*all).ii + i], 1, ".xpm");
	if ((*all).line[(*all).ii] == 'W' && (*all).line[(*all).ii + 1] == 'E')
		texture1(all, &(*all).line[(*all).ii + i], 2, ".xpm");
	if ((*all).line[(*all).ii] == 'E' && (*all).line[(*all).ii + 1] == 'A')
		texture1(all, &(*all).line[(*all).ii + i], 3, ".xpm");
	if ((*all).line[(*all).ii] == 'S' && (*all).line[(*all).ii + 1] == '2')
		texture1(all, &(*all).line[(*all).ii + i], 4, ".xpm");
	if ((*all).line[(*all).ii] == 'S' && (*all).line[(*all).ii + 1] == '3')
		texture1(all, &(*all).line[(*all).ii + i], 5, ".xpm");
	if ((*all).line[(*all).ii] == 'S' && (*all).line[(*all).ii + 1] == '4')
		texture1(all, &(*all).line[(*all).ii + i], 6, ".xpm");
}

/*****************************************
*	1.3.4.1.2. paste_r_f_c_error         *
******************************************
*	Check error extention (too small, too big).
*/

void	paste_r_f_c_error(t_mlx *all, int iter)
{
	if (iter == 2 && (((*all).r_xy[0] < 2 || (*all).r_xy[1] < 2)))
		write(1, "Error\nR cannot be zero or less two.\n", 37);
	if ((*all).line[(*all).ii])
		write(1, "Error\nwrong end of string\n", 27);
	if ((((*all).r_xy[0] < 2 || (*all).r_xy[1] < 2) && iter == 2)
		|| (*all).line[(*all).ii])
	{
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
	if (!(*all).win && ((*all).r_xy[0] >= 10000 || (*all).r_xy[1] >= 10000))
	{
		write(1, "Error\nToo big extention for .bmp.\n", 35);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
}

/*****************************************
*	1.3.4.1. paste_r_f_c_part1           *
******************************************
*	Paste parameters R F C.
*
*	functions:
*	1.3.4.1.1. paste_r_f_c_part2
*	1.3.4.1.2. paste_r_f_c_error
*/

void	paste_r_f_c_part1(t_mlx *all, unsigned int *rfc, char c, int iter)
{
	char	comma_space;
	int		i;

	i = -1;
	comma_space = ' ';
	if ((*all).line[(*all).ii] == 'R')
		(*all).does_paste_r += 1;
	if ((*all).line[(*all).ii] == 'F')
		(*all).does_paste_f += 1;
	(*all).does_paste_c += ((*all).line[(*all).ii] == 'C');
	(*all).ii++;
	while (++i < iter)
	{
		(*all).i = i;
		paste_r_f_c_part2(all, &(rfc[i]), comma_space, iter);
		comma_space = c;
	}
	paste_r_f_c_error(all, iter);
}

/*****************************************
*	1.3.4.1.1. paste_r_f_c_part2         *
******************************************
*	Paste parameters R F C.
*
*	functions:
*	1.3.4.1.1. exit_clean
*		main_2_start_all.c
*	1.3.4.1.2. atoi_only_digit
*		./map/libft_add_functions.c
*/

void	paste_r_f_c_part2(t_mlx *all, unsigned int *rfc,
		char comma_space, int iter)
{
	if ((*all).line[(*all).ii] != comma_space)
	{
		write(1, "Error\ndelimiter error\n", 23);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
	(*all).ii++;
	while ((*all).line[(*all).ii] == ' ')
		(*all).ii++;
	if ((*all).line[(*all).ii])
		*rfc = atoi_only_digit(all, 0);
	if (((*all).line[(*all).ii] && (int)((*all).i + 1) == iter)
		|| (*rfc > 255 && iter == 3))
	{
		write(1, "Error\nF or C - wrong color, or wrong R\n", 40);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
	while ((*all).line[(*all).ii] >= '0' && (*all).line[(*all).ii] <= '9')
		(*all).ii++;
}
