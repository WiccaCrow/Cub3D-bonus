#include "../cub3D.h"

int	color_wall(t_mlx *all, float height_w, int h, float k_p_w)
{
	int		color;
	float	k;
	int		y;
	int		flag;
	int		x;

	flag = 3;
	if ((*all).wall_color == 'N')
		flag = 0;
	if ((*all).wall_color == 'S')
		flag = 1;
	if ((*all).wall_color == 'W')
		flag = 2;
	if ((*all).map[(int)(*all).x_w][(int)(*all).y_w] == '4')
		flag = 6;
	k = (*all).texture_nswe_s[flag].height / height_w;
	y = (*all).texture_nswe_s[flag].height * k_p_w + (float)h * k;
	if (ft_strchr("NS", (*all).wall_color))
		x = (*all).texture_nswe_s[flag].width * ((*all).y_w - (int)(*all).y_w);
	else
		x = (*all).texture_nswe_s[flag].width * ((*all).x_w - (int)(*all).x_w);
	color = my_mlx_pix_take(&(*all).texture_nswe_s[flag], x, y);
	return (color);
}

void	texture1(t_mlx *all, char *str, int flag, char *extension)
{
	int	str_i;
	int	i;

	str_i = ft_strlen(str);
	i = 5;
	while (--i)
	{
		if (str[str_i - i] != extension[4 - i])
		{
			write(1, "Error\nTexture's format is bad.\n", 32);
			close ((*all).fd);
			exit_clean(all, -1, 0);
		}
	}
	(*all).nswe_s[flag] = 1;
	if ((*all).texture_nswe_s[flag].img)
	{
		write(1, "Error\nre-fill the textures.\n", 29);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
	texture2(all, str, flag, 0);
}

void	texture2(t_mlx *m, char *str, int f, int fd)
{
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\nTexture. The file does not exist or is bad.\n", 51);
		close ((*m).fd);
		exit_clean(m, -1, 0);
	}
	close(fd);
	(*m).texture_nswe_s[f].img = mlx_xpm_file_to_image((*m).mlx, str,
			&(*m).texture_nswe_s[f].width, &(*m).texture_nswe_s[f].height);
	if ((*m).texture_nswe_s[f].img)
		(*m).texture_nswe_s[f].addr
			= mlx_get_data_addr((*m).texture_nswe_s[f].img,
				&(*m).texture_nswe_s[f].b_p_p,
				&(*m).texture_nswe_s[f].line_l,
				&(*m).texture_nswe_s[f].endian);
	if (!((*m).texture_nswe_s[f].addr))
	{
		write(1, "Error\nmlx error (addr or img).\n", 32);
		close ((*m).fd);
		exit_clean(m, -1, 0);
	}
}

unsigned int	my_mlx_pix_take(t_img *map, int x, int y)
{
	char	*dst;

	dst = map->addr + (x * map->b_p_p / 8 + y * map->line_l);
	return (*(unsigned int *)dst);
}

void	my_mlx_pix_put(t_img *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (x * map->b_p_p / 8 + y * map->line_l);
	*(unsigned int *)dst = color;
}
