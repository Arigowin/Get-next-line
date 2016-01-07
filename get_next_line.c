/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 13:16:05 by dolewski          #+#    #+#             */
/*   Updated: 2016/01/07 13:36:26 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int		gnl_join(char **dest, char *src)
{
	char			*tmp;

	if (*dest == NULL)
	{
		ft_strdel(dest);
		if (!(*dest = ft_strdup(src)))
			return (-1);
	}
	else
	{
		if (!(tmp = ft_strjoin(*dest, src)))
			return (-1);
		ft_strdel(dest);
		if ((*dest = ft_strdup(tmp)) == NULL)
			return (-1);
		ft_strdel(&tmp);
	}
	return (0);
}

int		gnl(char **tmp_buff, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*tmp_buff)[i] != '\n')
		i++;
	(*tmp_buff)[i] = '\0';
	if (gnl_join(line, *tmp_buff) == -1)
		return (-1);
	(*tmp_buff)[i] = '\n';
	if ((tmp = ft_strsub(*tmp_buff, i + 1, ft_strlen(*tmp_buff))) == NULL)
		return (-1);
	ft_strdel(tmp_buff);
	if (gnl_join(tmp_buff, tmp) == -1)
		return (-1);
	free(tmp);
	return (1);
}

int		gnl_read(int fd, char **line, char **tmp_buff)
{
	int				len_buff;
	char			buff[BUFF_SIZE + 1];

	if (ft_strchr(*tmp_buff, '\n') != NULL)
		return (gnl(tmp_buff, line));
	while ((len_buff = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[len_buff] = '\0';
		if (gnl_join(tmp_buff, buff) == -1)
			return (-1);
		if (ft_strchr(*tmp_buff, '\n') != NULL)
			return (gnl(tmp_buff, line));
		ft_bzero(buff, BUFF_SIZE);
	}
	return (len_buff);
}

int		get_next_line(int const fd, char **line)
{
	static char		*tmp_buff[INT_MAX];
	int				ret;

	if (line == NULL || fd < 0)
		return (-1);
	else
		*line = NULL;
	if ((ret = gnl_read(fd, line, &(tmp_buff[fd]))) == -1)
		return (-1);
	else if (ret == 0)
	{
		if (tmp_buff[fd] && tmp_buff[fd][0])
		{
			if ((*line = ft_strdup(tmp_buff[fd])) == NULL)
				return (-1);
			ft_strdel(&(tmp_buff[fd]));
			return (1);
		}
		else if (*line)
			return (1);
		ft_strdel(&(tmp_buff[fd]));
		return (0);
	}
	return (1);
}
