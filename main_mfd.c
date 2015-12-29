
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

	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[2], O_RDONLY);
	fd[2] = open(av[3], O_RDONLY);
	fd[3] = open(av[4], O_RDONLY);
	ac = 0;

	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd[i], &line);

		printf("%d->%d->%s\n", ret, fd[i], line);
		free(line);
		line = NULL;
		i = (i == 1 ? 0 : i + 1);
	}

	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (0);
}
