/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 13:16:05 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/19 14:10:26 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

int		gnl(char **tmp_buff, char **line)
{
	char			*sub;
	int				i;

	printf("fuck%s\n", *tmp_buff);
	if ((*tmp_buff) != NULL)
	{
		printf("fuck\n");
		i = 0;
		while ((*tmp_buff)[i] && (*tmp_buff)[i] != '\n')
			i++;
		if (!(*line = ft_strsub((*tmp_buff), 0, i)))
			return (-1);
		if (!(sub = ft_strsub((*tmp_buff), i + 1, ft_strlen((*tmp_buff)) - i)))
			return (-1);
		ft_strdel(tmp_buff);
		if ((*tmp_buff = ft_strdup(sub)) != NULL)
		{
			if (sub[0] == '\0')
				ft_strdel(tmp_buff);
			ft_strdel(&sub);
			return (1);
		}
	}
	return (0);
}

int		gnl_for_norme(char **tmp_buff, char **buff)
{
	char			*tmp;

	if ((*tmp_buff) == NULL)
	{
		ft_strdel(tmp_buff);
		if (!((*tmp_buff) = ft_strdup(*buff)))
			return (-1);
	}
	else
	{
		if (!(tmp = ft_strjoin((*tmp_buff), *buff)))
			return (-1);
		ft_strdel(tmp_buff);
		*tmp_buff = ft_strdup(tmp);
		ft_strdel(&tmp);
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
		if (gnl_for_norme(tmp_buff, &buff) == -1)
			return (-1);
		ft_strdel(&buff);
		if (!(buff = ft_strnew(BUFF_SIZE)))
			return (-1);
		ft_bzero(buff, BUFF_SIZE);
	}
	ft_strdel(&buff);
	return (len_buff);
}

t_file **ft_search(t_file **lst, int fd)
{
	while (*lst != NULL)
	{
		if ((*lst)->fd == fd)
			break;
		(*lst) = (*lst)->next;
	}
	return (lst);
}

int		get_next_line(int const fd, char **line)
{
	//static char		*tmp_buff[1024];
	static t_file	*tmp_buff;
	t_file			**tmp;
	int				ret;
	char *t;

	t = ft_strnew(1);
	tmp = &tmp_buff;
	ft_search(&tmp_buff, fd);
	t[0] = 'a';
	if (tmp_buff == NULL)
	{
		ft_lstfileadd(&tmp_buff, ft_lstfilenew(t, fd));
	}
	printf("fuck%s\n", tmp_buff->data);

	if (line == NULL)
		return (-1);
	if ((ret = gnl(&(tmp_buff->data), line)) == -1)
		return (-1);
	else if (ret == 1)
	{
		tmp_buff = *tmp;
		return (1);
	}
	if ((gnl_read(fd, &(tmp_buff->data))) == -1)
		return (-1);
	printf("XD%s\n", tmp_buff->data);
	if ((ret = gnl(&(tmp_buff->data), line)) == -1)
		return (-1);
	else if (ret == 1)
	{
		tmp_buff = *tmp;
		return (1);
	}
	ft_lstfilefree(&tmp_buff);
	tmp_buff = *tmp;
	return (0);
}
