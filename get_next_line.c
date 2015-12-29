/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 13:16:05 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/29 13:12:14 by dolewski         ###   ########.fr       */
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

	if (tmp_buff != NULL && (*tmp_buff) != NULL)
	{
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

int		get_next_line(int const fd, char **line)
{
	//static char		*tmp_buff[1024];
	static t_file	tmp_buff;
	t_file			*tmp;
	int				ret;

	if (line == NULL)
		return (-1);
	tmp = &tmp_buff;
	if (tmp->data == NULL && tmp->fd == 0)
	{
		tmp_buff.fd = fd;
		tmp_buff.next = NULL;
		tmp_buff.data = ft_strnew(1);
		if ((ret = gnl_read(fd, &(tmp->data))) == -1)
			return (-1);
	}
	while (tmp->fd != fd && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->fd != fd)
	{
		if ((tmp->next = (t_file*)malloc(sizeof(t_file))) == NULL)
			return (-1);
		tmp->next->fd = fd;
		tmp->next->next = NULL;
		tmp->next->data = NULL;
		if ((ret = gnl_read(fd, &(tmp->next->data))) == -1)
			return (-1);
		tmp = tmp->next;
	}
	if ((ret = gnl(&(tmp->data), line)) == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	return (0);
}
