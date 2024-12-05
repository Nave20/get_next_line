#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ((int) write(fd, "(null)", 6));
	return ((int) write(fd, s, ft_strlen(s)));
}
int main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	return (0);
}