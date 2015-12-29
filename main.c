
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	int fd[2];
	int ret;
	char *line;

	ac = 0;
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[2], O_RDONLY);

	ret = get_next_line(fd[0], &line);
	if (ret == -1)
		printf("error: fd->|%d| ret->|%d|\n", fd[0], ret);
	printf("%d->%d->%s\n", ret, fd[0], line);
	free(line);
	line = NULL;

	ret = get_next_line(fd[1], &line);
	if (ret == -1)
		printf("error: fd->%d ret->%d\n", fd[1], ret);
	printf("%d->%d->%s\n", ret, fd[1], line);
	free(line);
	line = NULL;

	ret = get_next_line(fd[0], &line);
	if (ret == -1)
		printf("error: fd->%d ret->%d\n", fd[0], ret);
	printf("%d->%d->%s\n", ret, fd[0], line);
	free(line);
	line = NULL;

	ret = get_next_line(fd[1], &line);
	if (ret == -1)
		printf("error: fd->%d ret->%d\n", fd[1], ret);
	printf("%d->%d->%s\n", ret, fd[1], line);
	free(line);
	line = NULL;

	ret = get_next_line(fd[0], &line);
	if (ret == -1)
		printf("error: fd->%d ret->%d\n", fd[0], ret);
	printf("%d->%d->%s\n", ret, fd[0], line);
	free(line);
	line = NULL;

	ret = get_next_line(fd[1], &line);
	if (ret == -1)
		printf("error: fd->%d ret->%d\n", fd[1], ret);
	printf("%d->%d->%s\n", ret, fd[1], line);
	free(line);
	line = NULL;

	close(fd[0]);
	close(fd[1]);
	return (0);
}
