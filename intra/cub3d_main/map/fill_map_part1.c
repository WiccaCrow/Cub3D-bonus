#include "../cub3D.h"

/*****************************************
*		1.3.6.2. nb_valid_map_lines      *
******************************************
*	Check valid every simbol of map in every string.
*
*	functions:
*	1.3.1. get_next_line (take next line from file)
*		./map/gnl
*	1.3.6.2.1. check_valid_every_maps_str
*	1.3.4.1.1. exit_clean
*		./map/fil_map_part2.c
*/

void	nb_valid_map_lines(t_mlx *all, int q_gnl, int gnl, char *line)
{
	int		fd2;

	fd2 = open((*all).argv1, O_RDONLY);
	while (--q_gnl && get_next_line(fd2, &line) > 0)
		if (line)
			free(line);
	while (gnl > 0)
	{
		(*all).nb_lines++;
		gnl = get_next_line(fd2, &line);
		check_valid_every_maps_str(all, line);
		if ((*all).len_str_max < ft_strlen(line))
			(*all).len_str_max = ft_strlen(line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close (fd2);
	if ((*all).nb_lines < 3)
	{
		write(1, "Error\nMap is bad.\n", 19);
		close((*all).fd);
		exit_clean(all, -1, 0);
	}
}

/*****************************************
*			1.3.6.    map    	         *
******************************************
*	Fill map.
*
*	functions:
*	1.3.6.1. check_paste_map_options
*	1.3.6.2. nb_valid_map_lines
*	1.3.6.3. paste_map_part1
*	1.3.3. ft_strchr
*	1.3.6.5. closed_map
*/

void	map(t_mlx *all, int q_gnl)
{
	int	i;
	int	j;

	check_paste_map_options(all);
	nb_valid_map_lines(all, q_gnl, 1, NULL);
	paste_map_part1(all);
	i = 1;
	while (i < (*all).nb_lines && ft_strchr(" 1", (*all).map[i][0]))
		++i;
	j = -1;
	while ((*all).map[0][++j])
	{
		if (!ft_strchr(" 1", (*all).map[0][j]) || i < (*all).nb_lines)
		{
			write(1, "Error\nNot a closed map.\n", 25);
			exit_clean(all, -1, 0);
		}
	}
	closed_map(all, -1, -1);
}

/*****************************************
*	1.3.6.1. check_paste_map_options     *
******************************************
*
*	functions:
*	1.3.4.1.1. exit_clean
*/

void	check_paste_map_options(t_mlx *all)
{
	int	i;

	if ((*all).does_paste_r != 1 || (*all).does_paste_f != 1
		|| (*all).does_paste_c != 1 || (*all).f_rgb[0] < 0
		|| (*all).f_rgb[1] < 0 || (*all).f_rgb[2] < 0
		|| (*all).c_rgb[0] < 0 || (*all).c_rgb[1] < 0
		|| (*all).c_rgb[2] < 0)
	{
		write(1, "Error\nsome of R, F, C bad filled or map not last.\n", 51);
		close((*all).fd);
		exit_clean(all, -1, 0);
	}
	i = -1;
	while (++i < 5)
	{
		if (!(*all).nswe_s[i])
		{
			write(1, "Error\nsome map opt. wasn't fill or map not last.\n", 50);
			close((*all).fd);
			exit_clean(all, -1, 0);
		}
	}
}

/*****************************************
*		1.3.6.3. paste_map_part1         *
******************************************
*	Fill map.
*
*	functions:
*	1.3.6.3.1. pointer_null
*	1.3.6.3.1. paste_map_part2
*	1.3.4.1.1. exit_clean
*/

void	paste_map_part1(t_mlx *all)
{
	int	i;

	(*all).map = malloc(((*all).nb_lines + 1) * sizeof(char *));
	pointer_null(all);
	if (!(*all).map)
	{
		write(1, "Error\nmalloc error\n", 20);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
	(*all).map[(*all).nb_lines] = NULL;
	i = -1;
	while (++i < (*all).nb_lines + 1)
		paste_map_part2(all, i, -1, 1);
	close ((*all).fd);
	if (!(*all).player)
	{
		write(1, "Error\nNo player.\n", 18);
		exit_clean(all, -1, 0);
	}
	if ((*all).line)
	{
		free((*all).line);
		(*all).line = NULL;
	}
}

/*****************************************
*		1.3.6.3.1. paste_map_part2       *
******************************************
*	Fill map.
*
*	functions:
*	1.3.4.1.1. exit_clean
*/

void	paste_map_part2(t_mlx *all, int	i, int j, int gnl)
{
	(*all).map[i] = ft_calloc((*all).len_str_max + 1, sizeof(char));
	if (!(*all).map[i])
	{
		write(1, "Error\nmalloc error\n", 20);
		close((*all).fd);
		exit_clean(all, -1, 0);
	}
	while ((*all).line[++j])
		(*all).map[i][j] = (*all).line[j];
	free((*all).line);
	(*all).line = NULL;
	gnl = get_next_line((*all).fd, &((*all).line));
	if (gnl < 0 || (gnl && !(*(*all).line))
		|| (i == (*all).nb_lines - 2 && !(*all).line[0]))
	{
		if (gnl < 0)
			write(1, "Error\nread error.\n", 19);
		else
			write(1, "Error\nwrong map's string delimiter.\n", 37);
		close((*all).fd);
		exit_clean(all, -1, 0);
	}
	while (j < (*all).len_str_max + 1)
		(*all).map[i][j++] = ' ';
}
