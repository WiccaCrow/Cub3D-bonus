#include "cub3D.h"

int	exit_clean2(t_mlx *all, int i, int ii)
{
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
	// system("killall afplay");
	system("killall -9 aplay");
	exit (1);
}
