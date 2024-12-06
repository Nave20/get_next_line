/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:00:31 by vpirotti          #+#    #+#             */
/*   Updated: 2024/11/29 14:00:31 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;

	if (src == NULL || size == 0)
		return (ft_strlen(src));
	index = 0;
	while (index < size - 1 && src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	len = ft_strlen(s2);
	j = ft_strlen(s1) + 1;
	i = 0;
	res = (char *) malloc ((j + len) * sizeof(char));
	if (!res)
		return (res);
	ft_strlcpy(res, s1, j);
	while (i < len)
	{
		res[j - 1] = s2[i];
		i++;
		j++;
	}
	res[j - 1] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i != start && s[i])
		i++;
	if (len > ft_strlen(s) - i)
		len = ft_strlen(s) - i;
	res = (char *) malloc ((len + 1) * sizeof (char));
	if (!res)
		return (res);
	while (j < len)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
