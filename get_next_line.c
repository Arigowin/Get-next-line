/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:01:18 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/11 19:54:15 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_read(int fd, char **line, char **tmp)
{
	char	*buff;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if ((buff = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	while ((len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[len] = '\0';

		while (buff && buff[i] != '\0')
		{
			if (buff[i] == '\n')
			{
				if (*tmp != NULL)
					*line = ft_strjoin(*tmp, ft_strsub(buff, 0, i));
				else
					*line = ft_strsub(buff, 0, i);
				*tmp = ft_strsub(buff, i + 1, len - i);
				if (*line != NULL && *tmp != NULL)
					return (1);
			}
			i++;
		}
		i = 0;
		if (*tmp)
		{
			if ((*tmp = ft_strjoin(*tmp, buff)) == NULL)
				return (-1);
		}
		else
		{
			if ((*tmp = ft_strdup(buff)) == NULL)
				return (-1);
		}
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char	*tmp = NULL;
	int			i;
	char		*tmp2;

	i = 0;
	tmp2 = NULL;
	while (tmp && tmp[i] != '\0')
	{
		if (tmp[i] == '\n')
		{
			if ((*line = ft_strsub(tmp, 0, i)) == NULL)
				return (-1);
			if ((tmp2 = ft_strsub(tmp, i + 1, ft_strlen(tmp) - i)) == NULL)
				return (-1);
			if ((tmp = ft_strdup(tmp2)) == NULL)
				return (-1);
			return (1);
		}
		i++;
	}
	return (gnl_read(fd, line, &tmp));
}
