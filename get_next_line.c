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
	char	*res;
	size_t	i;

	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
		{
			break ;
		}
	}
	res = ft_substr(buffer, i + 1, ft_strlen(buffer));
	if (!res)
		return (NULL);
	return (res);
}

size_t	eol_detector(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
				return (0);
		}
		i++;
	}
	return (1);
}

char	*get_buffer(int fd, char *buffer, ssize_t *stop)
{
	size_t		stop2;
	char		*res;

	stop2 = 1;
	res = NULL;
	while (*stop && stop2)
	{
		*stop = read(fd, buffer, BUFFER_SIZE);
		if (*stop == -1)
			return (NULL);
		if (*stop == 0)
			break ;
		buffer[*stop] = 0;
		stop2 = eol_detector(buffer);
		res = ft_strjoin(res, buffer);
		if (!res)
			return (NULL);
	}
	return (res);
}

char	*gnl_core(int fd, char *buffer, ssize_t *stop)
{
	char	*res;
	char	*temp;

	res = get_buffer_nl(buffer);
	if (!res)
		return (NULL);
	if (eol_detector(res) != 0 && *stop == BUFFER_SIZE)
	{
		temp = get_buffer(fd, buffer, stop);
		if (!temp)
			return (free(res), NULL);
		res = ft_strjoin(res, temp);
		if (!res)
			return (free(temp), free(res), NULL);
		free(temp);
	}
	if (*stop < BUFFER_SIZE)
		ft_strlcpy(buffer, res, BUFFER_SIZE);
	// if (eol_detector(res) != -1)
	res = ft_snip(res);
	return (res);
}

char	*get_next_line(int fd)
{
	char			*res;
	ssize_t			stop;
	static char		buffer[BUFFER_SIZE + 1] = "\0";

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stop = 1;
	if (buffer[0] == 0)
	{
		res = get_buffer(fd, buffer, &stop);
		if (!res)
			return (NULL);
		if (res[ft_strlen(res) - 1] == '\n' || stop < BUFFER_SIZE)
			res = ft_snip(res);
	}
	else
		res = gnl_core(fd, buffer, &stop);
	if (res[0] == 0)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
