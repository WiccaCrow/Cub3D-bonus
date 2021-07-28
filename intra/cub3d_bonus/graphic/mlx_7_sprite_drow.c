#include "../cub3D.h"

void	sprite_drow1(t_mlx *all, float dist_plane, int j, int i)
{
	t_spr		*sp;
	float		spr_h;

	sp = sprite_sort(all, 0, 0, -1);
	while (sp[++i].x)
	{
		spr_h = dist_plane / sp[i].dist;
		(*all).spr_tex = sp[i].spr;
		j = 0;
		if (sp[i].i - spr_h / 2 < 0)
			j = spr_h / 2 - sp[i].i;
		while ((j - (int)spr_h) && (sp[i].i - (int)spr_h
				/ 2 + j) < (int)(*all).r_xy[0])
		{
			if (sp[i].i + spr_h / 2 > 0)
				if ((spr_h * (*all).pl_h_bonus / (float)SIZE_BLOCK)
					> ((dist_plane
							/ (*all).dist_wall[sp[i].i - (int)spr_h / 2 + j])
						* (*all).pl_h_bonus / (float)SIZE_BLOCK))
					sprite_drow2(all, spr_h, sp[i].i - spr_h / 2 + j + 1, j);
			++j;
		}
	}
	free(sp);
}

void	sprite_drow2(t_mlx *all, float height, float x, int j)
{
	int		i;
	int		color;
	float	pl_height;

	pl_height = height * (*all).pl_h_bonus / (float)SIZE_BLOCK;
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

int	color_sprite(t_mlx *all, float height_s, int h, int j)
{
	int		color;
	float	k;
	int		y;
	int		x;
	int		flag;

	flag = (*all).spr_tex - '0' + 2;
	k = (*all).texture_nswe_s[flag].height / height_s;
	y = (*all).texture_nswe_s[flag].height * (*all).k_view_hight
		+ (float)h * k - 1;
	k = (*all).texture_nswe_s[flag].width / height_s;
	x = (*all).texture_nswe_s[flag].width + (float)j * k;
	color = my_mlx_pix_take(&(*all).texture_nswe_s[flag], x, y);
	return (color);
}
