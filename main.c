#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	char *line;
	int i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i++ < 8)
	{
		line = get_next_line(fd);
		printf("line number %i : %s",i, line);
		free(line);
	}

	return (0);
}