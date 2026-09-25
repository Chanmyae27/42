/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:57:21 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/24 19:46:57 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(char *buffer, int fd)
{
	char	*temp;
	long	bytes;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free (buffer), NULL);
	bytes = 1;
	while (!ft_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (free (temp), free (buffer), NULL);
		temp[bytes] = '\0';
		if (!buffer && bytes > 0)
			buffer = ft_substr(temp, 0, bytes);
		else if (bytes > 0)
			buffer = ft_strjoin(buffer, temp);
		if (!buffer && bytes > 0)
			return (free (temp), NULL);
	}
	free (temp);
	if (!buffer || !*buffer)
		return (free (buffer), NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;
	char		*temp;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_file(buffer, fd);
	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	res = ft_substr(buffer, 0, i);
	temp = ft_substr(buffer, i, ft_strlen(buffer) - i);
	free (buffer);
	buffer = temp;
	if (!res)
		return (free (buffer), buffer = NULL, NULL);
	return (res);
}
