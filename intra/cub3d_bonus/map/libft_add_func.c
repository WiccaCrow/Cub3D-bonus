#include "../cub3D.h"

/*****************************************
*		1.3.4.1.2. atoi_only_digit       *
******************************************
*	Convers string to digit. Integer.
*/

unsigned int	atoi_only_digit(t_mlx *all, unsigned long int n)
{
	int	iter_max;

	iter_max = 21;
	if (!((*all).line[(*all).ii] >= '0' && (*all).line[(*all).ii] <= '9'))
	{
		write(1, "Error\nor R, or F, or C is not unsigned digit\n", 46);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
	while ((*all).line[(*all).ii] >= '0'
		&& (*all).line[(*all).ii] <= '9' && iter_max--)
	{
		n = n * 10 + ((*all).line[(*all).ii++] - '0');
		if (iter_max == 2 && (*all).line[(*all).ii] > '5')
			iter_max--;
	}
	if ((n > 2147483647) || (iter_max == 0
			|| (iter_max == 1 && n == 1844674407370955161u)))
	{
		write(1, "Error\ntoo large number in parameter\n", 37);
		close ((*all).fd);
		exit_clean(all, -1, 0);
	}
	return (n);
}

/*****************************************
*			1.3.3. ft_strchr 		     *
******************************************
*	searches for a character in the given string.
*	Returns a pointer to a character, or 0 
*	(no character found).
*/

char	*ft_strchr(const char *s, int c)
{
	while (*(s) != (char)c)
		if (*(s++) == '\0')
			return (0);
	return ((char *)s);
}

void	pointer_null(t_mlx *all)
{
	int	i;

	i = 0;
	while (i < (*all).nb_lines + 1)
		(*all).map[i++] = NULL;
}
