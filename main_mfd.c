
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	int fd[ac];
	int ret;
	char *line;
	int i;

	i = 0;
	while (i < ac - 1)
	{
		fd[i] = open(av[i + 1], O_RDONLY);
		i++;
	}
//	fd[0] = 0;

	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd[i], &line);
		printf("|%d|->|%d|\t|%s|\n", ret, fd[i], line);
		ft_strdel(&line);
		i = (i == (ac - 2) ? 0 : i + 1);
	}

	printf("ret:|%d|\tline:|%s|\n", ret, line);

	i = 0;
	while (i < ac - 1)
	{
		close(fd[i]);
		i++;
	}

//	while (1);
	return (0);
}
