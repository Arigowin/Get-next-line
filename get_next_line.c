/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 13:34:30 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/14 13:35:36 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static void		gnl_cond_read(char **tmp, char **buff)
{
	if (*tmp == NULL)
		*tmp = ft_strdup(*buff);
	else
		*tmp = ft_strjoin(*tmp, *buff);
}

static int		gnl_read(int fd, char **line, char ***buff_tmp, int j)
{
	char			*buff;
	int				len;
	size_t			i;
	char			*tmp;

	i = 0;
	tmp = NULL;
	if ((buff = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	while ((len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[len] = '\0';
		gnl_cond_read(&tmp, &buff);
	}
	if (tmp != NULL)
	{
		if ((*buff_tmp = ft_strsplit(tmp, '\n')) == NULL)
			return (-1);
		if ((*line = ft_strdup((*buff_tmp)[j])) != NULL)
			return (1);
	}
	if (len == -1)
		return (-1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		**buff_tmp = NULL;
	static int		j = 0;

	if (buff_tmp != NULL)
	{
		j++;
		if (buff_tmp[j] == NULL)
			return (0);
		*line = ft_strdup(buff_tmp[j]);
		if (*line != NULL)
			return (1);
		else
			return (-1);
	}
	return (gnl_read(fd, line, &buff_tmp, j));
}
