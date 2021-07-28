/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdulcie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 05:12:53 by mdulcie           #+#    #+#             */
/*   Updated: 2020/12/17 23:29:19 by mdulcie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line_for_new_norm(t_gnl *all, char	**end, int fd)
{
	(*all).i = ft_strchr_i((*all).buff, '\n');
	(*all).ret = read(fd, (*all).buff, BUFFER_SIZE);
	if ((*all).ret < 0 || BUFFER_SIZE <= 0)
		return (free_all(all, end));
	(*all).i = ft_strchr_i((*all).buff, '\n');
	if ((*all).i >= 0 && (*all).ret > 0)
	{
		*end = ft_strdup_free(&((*all).buff[(*all).i + 1]), *end, 1);
		if (!*end)
			return (free_all(all, end));
	}
	if (*end)
		(*all).buff[(*all).i] = '\0';
	(*all).str = ft_strjoin((*all).str, &((*all).buff), -1);
	if (!((*all).str) && (*all).ret > 0)
		return (free_all(all, end));
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*end;
	t_gnl		all;

	all.str = NULL;
	all.buff = ft_calloc(BUFFER_SIZE, sizeof(char));
	all.str = check_remain(&end, NULL);
	if (!line || fd < 0 || !(all.buff) || !(all.str))
		return (free_all(&all, &end));
	all.ret = 1;
	all.i = -1;
	while (all.i < 0 && all.ret && !end)
		if (get_next_line_for_new_norm(&all, &end, fd) == -1)
			return (-1);
	*line = fill_in_line(&(all.str), &(all.buff), &end, all.ret);
	if (!(*line))
		return (-1);
	if ((end == NULL) && (all.ret == 0))
		return (0);
	return (1);
}

char	*check_remain(char **end, char *str)
{
	int		i;

	if (!(*end))
		return (ft_strdup_free("", NULL, 2));
	if (*end)
	{
		i = ft_strchr_i(*end, '\n');
		if (i >= 0)
		{
			str = ft_strdup_free(*end, NULL, 0);
			*end = ft_strdup_free(&(*end)[i + 1], *end, 1);
			if (!str || !(*end))
				return (NULL);
		}
		else
		{
			str = ft_strdup_free(*end, NULL, 2);
			if (!str)
				return (NULL);
			if (*end != NULL)
				free(*end);
			*end = NULL;
		}
	}
	return (str);
}

char	*ft_strdup_free(const char *s1, char *s2, int flag)
{
	char	*c_copy;
	int		len;

	if (flag == 0)
		len = ft_strchr_i(s1, '\n');
	else
		len = ft_strlen(s1);
	c_copy = ft_calloc(len, sizeof(char));
	if (!c_copy)
		return (NULL);
	while (len--)
		c_copy[len] = s1[len];
	if (s2 != NULL && flag == 1)
	{
		free(s2);
		s2 = NULL;
	}
	return (c_copy);
}

char	*fill_in_line(char **str, char **buff, char **end, int ret)
{
	char	*line;

	line = ft_strdup_free(*str, NULL, 2);
	if (*buff)
	{
		free(*buff);
		*buff = NULL;
	}
	free(*str);
	*str = NULL;
	if (*end && ret == 0)
	{
		free(*end);
		*end = NULL;
	}
	return (line);
}
