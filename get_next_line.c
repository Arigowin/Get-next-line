/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:01:18 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/10 21:33:05 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		gnl_read(int fd, char **line, char **tmp)
{
	char	*buff;
	int		i;
	int		len;

	i = 0;
	len = 0;
	buff = ft_strnew(BUFF_SIZE);
	while ((len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[len] = '\0';

		while (buff && buff[i])
		{
			if (buff[i] == '\n')
			{
				if (*tmp != NULL)
					if ((*line = ft_strsub(buff, 0, i - 1)) == NULL)
						return (-1);
				if (*tmp != NULL)
					if ((*line = ft_strjoin(*tmp, ft_strsub(buff, 0, i - 1))) == NULL)
						return (-1);
				if ((*tmp = ft_strsub(buff, i + 1, len)) == NULL)
					return (-1);
				return (1);
			}
			i++;
		}

		if (*tmp == NULL)
		{
			if ((*tmp = ft_strsub(buff, 0, len)) == NULL)
				return (-1);
		}
		else
		{
			if ((*tmp = ft_strjoin(*tmp, buff)) == NULL)
				return (-1);
		}

	/*	while (buff[i] && buff[i] != '\n')
			i++;
		*line = ft_strsub(buff, 0, i);
		tmp = ft_strsub(buff, i + 1, ft_strlen(buff));
		if (buff[i] == EOF)
			return (0);
		return (1);*/
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char	*tmp;

	return (gnl_read(fd, line, &tmp));
/*	i = 0;
	j = 0;
	if (tmp != NULL)
	{
		while (tmp[i] != '\n' && tmp[i])
			i++;
		*line = ft_strsub(tmp, 0, i);
		tmp = ft_strsub(tmp, i + 1, ft_strlen(tmp));
		i++;
		if (tmp[i] == '\0')
			tmp = NULL;
		return (1);
	}*/
	return (-1);
}

#include <fcntl.h>

int main(int ac, char **argc)
{
	char *line;

	while (get_next_line(open(argc[1], O_RDONLY), &line) > 0)
		printf("main\t\t%sfin\n", line);
}
