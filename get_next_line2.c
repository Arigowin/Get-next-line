/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 13:34:30 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/14 13:56:32 by dolewski         ###   ########.fr       */
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

static int		gnl_read(int fd, char **line, t_buff *buff_tmp)
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
		if (((*buff_tmp).buff_t = ft_strsplit(tmp, '\n')) == NULL)
			return (-1);
		if ((*line = ft_strdup((*buff_tmp).buff_t[(*buff_tmp).j])) != NULL)
			return (1);
	}
	if (len == -1)
		return (-1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_buff		buff_tmp;

	if (buff_tmp.buff_t != NULL)
	{
		buff_tmp.j++;
		if (buff_tmp.buff_t[buff_tmp.j] == NULL)
			return (0);
		*line = ft_strdup(buff_tmp.buff_t[buff_tmp.j]);
		if (*line != NULL)
			return (1);
		else
			return (-1);
	}
	return (gnl_read(fd, line, &buff_tmp));
}
