#include "./cub3D.h"

/*****************************************
*	1.2. check_extention_argv 		     *
******************************************
*/

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

/*****************************************
*	1. 			main 				    *
******************************************
*	1. Main function. Runs the program.
*	2. Runs the function for checking the correct input of arguments.
*	3. Opens the first argument.
*	4. Decides, depending on the second argument, to open a window or take a 
*		screenshot.
*	5. After all drow frames.
*
*	self functions:
*	1.1. start_mlx
*	1.2. check_extention_argv
*	1.3. parser_valid_argv1	
*	1.4. ft_mlx_functions
*/

int	main(int argc, char **argv)
{
	t_mlx	al;

	start_mlx(&al);
	if (argc == 2 || argc == 3)
	{
		check_extention_argv(argv[1], ".cub", 0);
		if (argc == 3)
			check_extention_argv(argv[2], "--save", 2);
		al.argv1 = argv[1];
		al.fd = open(al.argv1, O_RDONLY);
		parser_valid_argv1(&al, 0, 1, 0);
		if (argc == 3)
			al.argv2 = 1;
		if (argc == 2)
			al.win = mlx_new_window(al.mlx, al.r_xy[0], al.r_xy[1], "W");
		if (argc == 2 && al.win == NULL)
			write(1, "Error\nmlx_new_window error\n", 28);
		if (!(argc == 2 && al.win == NULL))
			ft_mlx_functions(&al);
	}
	else
		write(1, "Error:\nwrong numbers of arguments (argc)\n", 41);
	exit_clean(&al, -1, 0);
	return (0);
}

/*****************************************
* 1.3.2. check_empty_line_beetwen_options*
******************************************
*	check lines beetwen NO SO WE EA S. Does it empty?
*/

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

/*****************************************
*	1.3.    parser_valid_argv1           *
******************************************
*	the function works with the first argument:
*	1. Reads the file with the map line by line.
*	2. Calls the function of checking empty lines between the map parameters
*		"NO SO WE EA S"
*	3. Checks which particular map parameter needs to be filled and calls 
*		the functions for filling the map and parameters from the argument.
*	4. Runs the function for checking the screen size and program window
*
*	functions:
*	1.3.1. get_next_line (take next line from file)
*		./map/gnl
*	1.3.2. check_empty_line_beetwen_options
*	1.3.3. ft_strchr 
*		./map/libft_add_functions.c
*	1.3.4. parser_r_f_c
*	1.3.5. paste_no_so_we_ea_s 
*		./map/fill_all_except_the_map.c
*	1.3.6. map
*	1.3.7. exit_clean
*	1.3.8. check_screen_size
*/

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
}

/*****************************************
*			1.3.4. parser_r_f_c          *
******************************************
*	Parses parameters R F C and runs functions 
*	for filling them.
*
*	functions:
*	1.3.4.1. paste_r_f_c_part1
*		./map/fill_all_except_the_map.c
*/

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
	if ((*all).r_xy[0] || (*all).r_xy[1])
		check_screen_size(all);
}
