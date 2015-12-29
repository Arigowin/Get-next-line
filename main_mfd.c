
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
	while (i < ac)
	{
		fd[i] = open(av[i + 1], O_RDONLY);
		i++;
	}

	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd[i], &line);
		printf("|%d|->|%d|->|%s|\n", ret, fd[i], line);
		free(line);
		line = NULL;
		i = (i == (ac - 2) ? 0 : i + 1);
	}

	i = 0;
	while (i < ac)
	{
		close(fd[i]);
		i++;
	}

	return (0);
}
