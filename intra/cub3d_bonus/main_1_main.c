#include "cub3D.h"

void	check_extention_argv(char *argv, char *cub_flag, int nb)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if ((i + 1) > (4 + nb))
		while (*cub_flag && !(argv[i++ - (4 + nb)] - *cub_flag))
			cub_flag++;
	if (*cub_flag)
	{
		write(1, "Error\nwrong extension of 1st argument or flag\n", 47);
		exit (1);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
 char		*ft_strdup(const char *s1)
{
	char	*c_copy;
	int		len;

	len = ft_strlen(s1);
	if ((c_copy = malloc((len + 1) * sizeof(char))) == 0)
		return (NULL);
	c_copy[len] = 0;
	while (len--)
	{
		c_copy[len] = s1[len];
	}
	return (c_copy);
}
///////////////////////////////////////////////////////////////////////////////////////
int	main(int argc, char **argv)
{
	t_mlx	al;

	start_mlx(&al);
	// if (argc == 2 || argc == 3)
	if (argc == 2 || argc == 3 || argc == 1)
	{
		// check_extention_argv(argv[1], ".cub", 0);
		if (argc == 3)
			check_extention_argv(argv[2], "--save", 2);
		al.argv1 = ft_strdup(argv[1]);
		// al.argv1 = "cubik_m.cub";
		// al.argv1 = "/home/wicca/Desktop/cub3D/intra/cubik_m.cub";
		al.fd = open(al.argv1, O_RDONLY);
		parser_valid_argv1(&al, 0, 1, 0);
		// if (argc == 2)
		if (argc != 3)
		{
			bonus_volume();
			al.win = mlx_new_window(al.mlx, al.r_xy[0], al.r_xy[1], "W");
		}
		// if (argc == 2 && al.win == NULL)
		if (argc != 3 && al.win == NULL)
			write(1, "Error\nmlx_new_window error\n", 28);
		// if (!(argc == 2 && al.win == NULL))
		if (!(argc != 3 && al.win == NULL))
			ft_mlx_functions(&al);
	}
	else
		write(1, "Error:\nwrong numbers of arguments (argc)\n", 41);
	exit_clean(&al, -1, 0);
	return (0);
}

void	check_empty_line_beetwen_options(t_mlx *all, int *i, int *q_gnl)
{
	++(*q_gnl);
	while ((*all).line[*i] == ' ')
	{
		++(*i);
		if (!(*all).line[*i])
		{
			write(1, "Error\nnot empty line between the map options.\n", 47);
			exit_clean(all, -1, 0);
		}
	}
}

void	parser_valid_argv1(t_mlx *all, int q_gnl, int gnl, int i)
{
	gnl = get_next_line((*all).fd, &(*all).line);
	while (gnl > 0)
	{
		check_empty_line_beetwen_options(all, &i, &q_gnl);
		if (ft_strchr("RFC", (*all).line[i]))
			parser_r_f_c(all, i);
		else if ((*all).line[i] && !ft_strchr(" 1", (*all).line[i]))
			paste_no_so_we_ea_s(all, i);
		else if ((*all).line[i])
		{
			map(all, q_gnl);
			break ;
		}
		free((*all).line);
		(*all).line = NULL;
		gnl = get_next_line((*all).fd, &(*all).line);
		i = 0;
	}
	if ((*all).fd >= 0 && gnl < 0)
		close ((*all).fd);
	if (gnl < 0)
		write(1, "Error\nfile with map was not open or read (gnl)\n", 48);
	if (gnl < 0)
		exit_clean(all, -1, 0);
	check_screen_size(all);
}

void	parser_r_f_c(t_mlx *all, int i)
{
	(*all).ii = i;
	if ((*all).line[i] == 'R')
		paste_r_f_c_part1(all, (*all).r_xy, ' ', 2);
	if ((*all).line[i] == 'F')
		paste_r_f_c_part1(all, (*all).f_rgb, ',', 3);
	if ((*all).line[i] == 'C')
		paste_r_f_c_part1(all, (*all).c_rgb, ',', 3);
	free((*all).line);
	(*all).line = NULL;
}
