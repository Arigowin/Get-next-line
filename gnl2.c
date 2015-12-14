#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>


# include <libft.h>

int		get_next_line(int const fd, char **line)
{
	static char		*tmp_buff;

	char			*buff;
	int				len_buff;

	char			*sub;
	int				i;

	if (ft_strchr(tmp_buff, '\n'))
	{
		i = 0;
		while (tmp_buff[i] != '\n')
			i++;
		*line = ft_strsub(tmp_buff, 0, i);
		sub = ft_strsub(tmp_buff, i, ft_strlen(tmp_buff));
		tmp_buff = ft_strjoin(tmp_buff, sub);
		return (1);
	}
	buff = ft_strnew(BUFF_SIZE + 1);
	while((len_buff = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if ((ft_strchr(buff, '\n')) == NULL)
		{
			if (tmp_buff == NULL)
				tmp_buff = ft_strdup(buff);
			else
				tmp_buff = ft_strjoin(tmp_buff, buff);
		}
		else
		{
			i = 0;
			while (buff[i] != '\n')
				i++;
			*line = ft_strsub(buff, 0, i);
			sub = ft_strsub(buff, i, ft_strlen(buff));
			if (tmp_buff == NULL)
			{
				tmp_buff = ft_strdup(sub);
			}
			else
			{
				tmp_buff = ft_strjoin(tmp_buff, sub);
			}
			return (1);
		}
	}
	if (len_buff == -1)
		return (-1);
	else if (len_buff == 0)
		return (0);
	else
		return (1);
}
