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

char	*get_buffer_nl(char *buffer, size_t eol)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(&buffer[eol]);
	temp = malloc (eol);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, buffer, eol);
	ft_strlcpy(buffer, &buffer[eol - 1], len + 2);
	return (temp);
}

size_t	eol_detector(const char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			return (i + 2);
		}
		i++;
	}
	return (0);
}

char	*get_buffer(int fd, char *buffer, ssize_t *stop)
{
	char		*res;
	size_t		eol;
	char		*temp;

	eol = 0;
	res = NULL;
	while (*stop == BUFFER_SIZE && eol == 0)
	{
		*stop = read(fd, buffer, BUFFER_SIZE);
		if (*stop == -1)
			return (ft_memset(buffer, 0, BUFFER_SIZE), NULL);
		buffer[*stop] = 0;
		eol = eol_detector(buffer);
		if (eol != 0)
		{
			res = ft_strjoin(res, temp = get_buffer_nl(buffer, eol));
			free(temp);
		}
		else
		{
			res = ft_strjoin(res, buffer);
			ft_memset(buffer, 0, BUFFER_SIZE + 1);
		}
	}
	return (res);
}

char	*gnl_core(int fd, char *buffer, ssize_t *stop)
{
	char	*temp;
	char	*ptr;
	char	*res;

	temp = ft_strdup(buffer);
	if (!temp)
		return (NULL);
	if (eol_detector(temp) != 0)
	{
		res = get_buffer_nl(buffer, eol_detector(temp));
		if (!res)
			return (free (temp), NULL);
		free (temp);
	}
	else
	{
		ptr = get_buffer(fd, buffer, stop);
		if (ptr == NULL)
			return (free(temp), NULL);
		res = ft_strjoin(temp, ptr);
		if (!res)
			return (free(ptr), NULL);
		free (ptr);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	char			*res;
	ssize_t			stop;
	static char		buffer[BUFFER_SIZE + 1] = "\0";

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stop = BUFFER_SIZE;
	res = NULL;
	if (buffer[0] == 0 || BUFFER_SIZE == 1)
	{
		res = get_buffer(fd, buffer, &stop);
	}
	else
	{
		res = gnl_core(fd, buffer, &stop);
	}
	if (!res)
		return (NULL);
	if (res[0] == 0)
	{
		free(res);
		return (NULL);
	}
	printf("%s", res);
	return (res);
}
