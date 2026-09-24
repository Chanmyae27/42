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

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	else if (nmemb && size > (size_t)-1 / nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_read_file(char *buffer, int fd)
{
	char	*temp;
	long	i;

	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	i = 1;
	while (!ft_strchr(buffer, '\n') && i)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i < 0 || (!i && !buffer))
		{
			free (temp);
			return (NULL);
		}
		temp[i] = '\0';
		if (!buffer)
			buffer = ft_strdup(temp);
		else
			buffer = ft_strjoin(buffer, temp);
		if (!buffer)
		{
			free (temp);
			return (NULL);
		}
	}
	free (temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;
	char		*temp;
	size_t			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_read_file(buffer, fd);
	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		++i;
	if (buffer[i] == '\n')
		++i;
	res = ft_substr(buffer, 0, i);
	temp = ft_substr(buffer, i, ft_strlen(buffer) - i);
	free (buffer);
	buffer = temp;
	return (res);
}
