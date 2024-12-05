/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:59:56 by vpirotti          #+#    #+#             */
/*   Updated: 2024/11/29 14:02:41 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_buffer_nl(char *buffer)
{
	char	temp[1];
	char	*res;
	size_t	i;

	i = 0;
	temp[0] = 0;
	while (buffer[i++])
	{
		if (buffer[i] == '\n')
			break;
	}
	res = ft_strjoin(temp, &buffer[i + 1]);
	if (!res)
		return (NULL);
	//printf("%s\n\n", res);
	return (res);
}

size_t	eol_detector(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*get_buffer(int fd, char *buffer)
{
	size_t		stop;
	size_t		stop2;
	char		*res;

	stop = 1;
	stop2 = 1;
	res = malloc(0);
	while (stop && stop2)
	{
		stop = read(fd, buffer, BUFFER_SIZE);
		if (stop == -1)
			return (NULL);
		if (stop == 0)
			break;
		stop2 = eol_detector(buffer);
		res = ft_strjoin(res, buffer);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*ft_snip(char *buffer)
{
	char	*res;
	size_t	temp;
	size_t	i;

	i = 0;
	temp = i;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (temp != i)
	{
		res = malloc (i - temp + 2);
		if (!res)
			return (NULL);
		ft_strlcpy(res, &buffer[temp], i - temp + 2);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	char			*res;
	char			*temp;
	char			*temp2;
	static char		buffer[BUFFER_SIZE + 1] = "\0";

	if (buffer[0] == 0)
	{
		res = get_buffer(fd, buffer);
		//res = ft_snip(buffer);
		printf("%s", res);
	}
	else
	{
		temp = get_buffer_nl(buffer);
		temp2 = get_buffer(fd, buffer);
		res = ft_strjoin(temp, temp2);
		res = ft_snip(res);
		free(temp);
		free(temp2);
		printf("%s", res);
	}
	return (NULL);
}