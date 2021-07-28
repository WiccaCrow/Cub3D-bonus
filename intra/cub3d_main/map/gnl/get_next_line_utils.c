/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdulcie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:16:20 by mdulcie           #+#    #+#             */
/*   Updated: 2020/12/10 22:16:24 by mdulcie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../../cub3D.h"

int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
		if (s[i++] == '\0')
			return (-1);
	return (i);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			i++;
	return (i);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*call;
	int		n;
	int		i;

	if (size < 1)
		return (NULL);
	n = (count + 1) * size;
	i = 0;
	call = malloc(n);
	if (call)
	{
		while (n--)
			call[i++] = 0;
		return (call);
	}
	return (NULL);
}

int	free_all(t_gnl *gnl, char **end)
{
	if (gnl->str != NULL)
	{
		free(gnl->str);
		gnl->str = NULL;
	}
	if (gnl->buff != NULL)
	{
		free(gnl->buff);
		gnl->buff = NULL;
	}
	if (*end != NULL)
	{
		free(*end);
		*end = NULL;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char **s2, int j)
{
	char	*join;
	int		i;

	i = ft_strlen(s1) + ft_strlen(*s2);
	join = ft_calloc(i + 1, sizeof(char));
	if (!join)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			join[i] = s1[i];
	if (*s2)
		while ((*s2)[++j])
			join[i + j] = (*s2)[j];
	join[j + i + 1] = '\0';
	if (s1 != NULL)
	{
		free(s1);
		s1 = NULL;
	}
	i = ft_strlen(*s2);
	while (i--)
		(*s2)[i] = 0;
	return (join);
}
