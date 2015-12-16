/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 13:16:05 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/16 13:26:45 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int		gnl(char **tmp_buff, char **line)
{
	char			*sub;
	int				i;

	if ((*tmp_buff) != NULL)
	{
		i = 0;
		while ((*tmp_buff)[i] && (*tmp_buff)[i] != '\n')
			i++;
		free(*line);
		if (!(*line = ft_strsub((*tmp_buff), 0, i)))
			return (-1);
		if (!(sub = ft_strsub((*tmp_buff), i + 1, ft_strlen((*tmp_buff)) - i)))
			return (-1);
		free((*tmp_buff));
		(*tmp_buff) = ft_strdup(sub);
		if ((*tmp_buff) != NULL)
		{
			if (sub[0] == '\0')
			{
				(*tmp_buff) = NULL;
				free(*tmp_buff);
			}
			free(sub);
			return (1);
		}
	}
	return (0);
}

int		gnl_read(int fd, char **tmp_buff)
{
	int				len_buff;
	char			*buff;

	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	ft_bzero(buff, BUFF_SIZE);
	while ((len_buff = read(fd, buff, BUFF_SIZE)) > 0)
	{
			free(*tmp_buff);
		if ((*tmp_buff) == NULL)
		{
			if (!((*tmp_buff) = ft_strdup(buff)))
				return (-1);
		}
		else
		{
			if (!((*tmp_buff) = ft_strjoin((*tmp_buff), buff)))
				return (-1);
		}
		free(buff);
		if (!(buff = ft_strnew(BUFF_SIZE)))
			return (-1);
		ft_bzero(buff, BUFF_SIZE);
	}
	free(buff);
	return (len_buff);
}

int		get_next_line(int const fd, char **line)
{
	static char		*tmp_buff;
	int				ret;

	if (line == NULL)
		return (-1);
	if ((ret = gnl(&tmp_buff, line)) == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	if ((gnl_read(fd, &tmp_buff)) == -1)
		return (-1);
	if ((ret = gnl(&tmp_buff, line)) == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	return (0);
}
