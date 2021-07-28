#include "../cub3D.h"

/*****************************************
*	1.3.6.2.1. check_valid_every_maps_str*
******************************************
*	Check valid every simbol of map in every string.
*
*	functions:
*	1.3.4.1.1. exit_clean
*		./map/fil_map_part2.c
*/

void	check_valid_every_maps_str(t_mlx *al, char *s)
{
	while (*s)
	{
		if (*s == '2')
			++((*al).nb_sprite);
		else if (!ft_strchr(" 01NEWS", *s))
		{
			write(1, "Error\nMap symbols are not valid.\n", 34);
			close((*al).fd);
			exit_clean(al, -1, 0);
		}
		else if (ft_strchr("NEWS", *s))
		{
			if ((*al).player == 0)
				(*al).player = *s;
			else
			{
				write(1, "Error\nPlayer should be 1.\n", 27);
				close((*al).fd);
				exit_clean(al, -1, 0);
			}
		}
		s++;
	}
}

/*****************************************
*		1.3.6.5. closed_map	             *
******************************************
*	Check closed map.
*
*	functions:
*	1.3.3. ft_strchr
*	1.3.6.5.1. map_char_around_space
*/

void	closed_map(t_mlx *all, int i, int j)
{
	char	c;
	int		iter;

	while (++i < (*all).nb_lines)
	{
		while ((*all).map[i][++j])
		{
			iter = 9;
			while (iter--)
			{
				if ((*all).map[i][j] == ' ')
					c = map_char_around_space(all, i, j, 8 - iter);
				else
					break ;
				if (!ft_strchr(" 1", c))
				{
					write(1, "Error\nNot a closed map.\n", 25);
					exit_clean(all, -1, 0);
				}
			}
		}
		j = -1;
	}
}

/*****************************************
*	1.3.6.5.1. map_char_around_space     *
******************************************
*	Check simbols around space. '1' or ' '.
*/

char	map_char_around_space(t_mlx *all, int i, int j, int around_space)
{
	int	ii;
	int	jj;

	ii = i + 1 - around_space / 3;
	jj = j + 1 - around_space % 3;
	if (ii >= 0 && jj >= 0 && ii < (*all).nb_lines && jj <= (*all).len_str_max)
		return ((*all).map[ii][jj]);
	return ((*all).map[i][j]);
}
