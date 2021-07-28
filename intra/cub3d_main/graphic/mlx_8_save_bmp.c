#include "../cub3D.h"

/*****************************************
*		1.4.6.2.2. save_bmp		 	     *
******************************************
*	Put image to do .bmp.
*
*	self functions:
*	1.4.6.2.2. bmp_header
*	1.4.6.2.2. bmp_image
*/

void	save_bmp(t_mlx *all)
{
	int	height;
	int	width;
	int	fd;

	width = (*all).r_xy[0];
	height = (*all).r_xy[1];
	fd = open("Deepthought.bmp", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	if (fd < 0)
		write(1, "Error\nDeepthought, error open/create bmp\n", 42);
	if (fd < 0)
		exit_clean(all, -1, 0);
	bmp_header(fd, width, height);
	bmp_image(fd, width, height, all);
	close (fd);
}

/*****************************************
*		1.4.6.2.2. bmp_header	 	     *
******************************************
*	self functions:
*	1.4.6.2.2.1. reverse_4_byte
*	1.4.6.2.2.2. reverse_2_byte
*/

void	bmp_header(int fd, int width, int height)
{
	int		bmp_size;
	int		i;
	char	buf[4];

	bmp_size = 14 + 40 + width * height * 4;
	write(fd, "BM", 2);
	write(fd, reverse_4_byte(bmp_size, buf), 4);
	write(fd, reverse_4_byte(0, buf), 4);
	write(fd, reverse_4_byte(54, buf), 4);
	write(fd, reverse_4_byte(40, buf), 4);
	write(fd, reverse_4_byte(width, buf), 4);
	write(fd, reverse_4_byte(height, buf), 4);
	write(fd, reverse_2_byte(1, buf), 2);
	write(fd, reverse_2_byte(32, buf), 2);
	i = 6;
	while (i--)
		write(fd, reverse_4_byte(0, buf), 4);
}

char	*reverse_4_byte(int bmp_size_or_color, char *buf)
{
	buf[3] = bmp_size_or_color >> 24;
	buf[2] = bmp_size_or_color >> 16;
	buf[1] = bmp_size_or_color >> 8;
	buf[0] = bmp_size_or_color;
	return (buf);
}

char	*reverse_2_byte(int bmp_size_or_color, char *buf)
{
	buf[1] = bmp_size_or_color >> 8;
	buf[0] = bmp_size_or_color;
	return (buf);
}

/*****************************************
*		1.4.6.2.2. bmp_image	 	     *
******************************************
*	Write image t .bmp file.
*/

void	bmp_image(int fd, int width, int height, t_mlx *mw)
{
	int		x;
	int		y;
	char	buf[4];
	int		color;

	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
		{
			color = my_mlx_pix_take(&(*mw).frame, y, height - x - 1);
			write(fd, reverse_4_byte(color, buf), 4);
		}
	}
}
