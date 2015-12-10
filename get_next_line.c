/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:01:18 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/10 20:10:42 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*gnl_build_line(char *buff, char *buff2)
{
	
}

int		get_next_line(int const fd, char **line)
{
	char	*buff;
	static char	*tmp;
	int		i;
	int		j;
	int		len;

	buff = ft_strnew(BUFF_SIZE);
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
	while ((len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[len] = '\0';
	/*	while (buff[i] && buff[i] != '\n')
			i++;
		*line = ft_strsub(buff, 0, i);
		tmp = ft_strsub(buff, i + 1, ft_strlen(buff));
		if (buff[i] == EOF)
			return (0);
		return (1);*/
	}
	return (-1);
}

#include <fcntl.h>

int main(int ac, char **argc)
{
	char *line;

	while (get_next_line(open(argc[1], O_RDONLY), &line) > 0)
		printf("main\t\t%sfin\n", line);
}
