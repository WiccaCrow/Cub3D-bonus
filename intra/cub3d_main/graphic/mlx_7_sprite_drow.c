#include "../cub3D.h"

/*****************************************
*	1.4.6.2.1.4. sprite_drow1		     *
******************************************
*	Runs the function for sorting sprites from 
*	far to near and draws the sprites.
*
*	self functions:
*	1.4.6.2.1.4.1. sprite_sort
*	1.4.6.2.1.4.2. sprite_drow2
*/

void	sprite_drow1(t_mlx *all, float dist_plane, int j)
{
	int			i;
	t_spr		*sp;
	float		s_height;

	sp = sprite_sort(all, 0, 0, -1);
	i = -1;
	while (sp[++i].x)
	{
		s_height = dist_plane / sp[i].dist;
		j = 0;
		if (sp[i].i - s_height / 2 < 0)
			j = s_height / 2 - sp[i].i;
		while ((j - (int)s_height) && (sp[i].i - (int)s_height
				/ 2 + j) < (int)(*all).r_xy[0])
		{
			if (sp[i].i + s_height / 2 > 0)
				if ((s_height * PL_HEIGHT / (float)SIZE_BLOCK) >= ((dist_plane
							/ (*all).dist_wall[sp[i].i - (int)s_height / 2 + j])
						* PL_HEIGHT / (float)SIZE_BLOCK))
					sprite_drow2(all, dist_plane
						/ sp[i].dist, sp[i].i - s_height / 2 + j + 1, j);
			++j;
		}
	}
	free(sp);
}

/*****************************************
*	1.4.6.2.1.4.2. sprite_drow2		     *
******************************************
*	Draws the sprites.
*
*	self functions:
*	1.4.6.2.1.3.2. my_mlx_pix_put
*	1.4.6.2.1.4.2.1.color_sprite
*/

void	sprite_drow2(t_mlx *all, float height, float x, int j)
{
	int		i;
	int		color;
	float	pl_height;

	pl_height = height * PL_HEIGHT / (float)SIZE_BLOCK;
	i = 0;
	while (i <= pl_height && i <= (int)(*all).r_xy[1] / 2)
	{
		color = color_sprite(all, height, i, j);
		if (color != COLOR_SKIP)
			my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 + i - 1, color);
		++i;
	}
	i = 1;
	while (i <= (height - pl_height) && ((*all).r_xy[1] / 2 - i + 1))
	{
		color = color_sprite(all, height, -i, j);
		if (color != COLOR_SKIP)
			my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 - i, color);
		++i;
	}
	if (i == (height - pl_height))
		if (color != COLOR_SKIP)
			my_mlx_pix_put(&(*all).frame, x, (*all).r_xy[1] / 2 - i, color);
}

/*****************************************
*	1.4.6.2.1.4.2.1.color_sprite	     *
******************************************
*	Find sprite' color in texture.
*
*	self functions:
*	1.4.6.2.1.3.1.1. my_mlx_pix_take
*/

int	color_sprite(t_mlx *all, float height_s, int h, int j)
{
	int		color;
	float	k;
	int		y;
	int		x;

	k = (*all).texture_nswe_s[4].height / height_s;
	y = (*all).texture_nswe_s[4].height * (*all).k_view_hight
		+ (float)h * k - 1;
	k = (*all).texture_nswe_s[4].width / height_s;
	x = (*all).texture_nswe_s[4].width + (float)j * k;
	color = my_mlx_pix_take(&(*all).texture_nswe_s[4], x, y);
	return (color);
}
