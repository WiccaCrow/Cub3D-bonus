#include "../cub3D.h"
#include <stdlib.h>

static char	*ft_charnbr(char *s, int n, int i, int flag)
{
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	if (n == 0)
		*s = '0';
	while (--i >= 0 && n != 0)
	{
		s[i] = n % 10 + '0';
		n /= 10;
	}
	if (flag)
		s[10] = '8';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		c;
	int		flag;

	flag = 0;
	i = 1;
	if (n == -2147483648)
		flag = 1;
	if (n == -2147483648)
		n++;
	c = n / 10;
	while (c)
	{
		c /= 10;
		i++;
	}
	if (n < 0)
		i++;
	s = (char *)malloc(sizeof(char) * ++i);
	if (!s)
		return (NULL);
	s[--i] = 0;
	s = ft_charnbr(s, n, i, flag);
	return (s);
}
