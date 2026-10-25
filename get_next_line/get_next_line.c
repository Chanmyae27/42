/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:57:21 by cmyae             #+#    #+#             */
/*   Updated: 2026/10/25 18:39:22 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_find(t_node *lst)
{
	size_t	i;

	while (lst)
	{
		i = 0;
		while (i < lst->len)
		{
			if (lst->content[i++] == '\n')
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_read_file(t_node **lst, t_node **last, int fd)
{
	char	*content;
	t_node	*node;
	int		bytes;

	content = malloc(BUFFER_SIZE + 1);
	if (!content)
		return (-1);
	bytes = read(fd, content, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free (content);
		return (bytes);
	}
	content[bytes] = '\0';
	node = ft_new_node(content, bytes);
	if (!node)
		return (-1);
	ft_add_back(lst, last, node);
	if (ft_find(node))
		return (2);
	return (1);
}

void	ft_shift_left(t_node *lst, size_t start)
{
	size_t	i;

	i = 0;
	while (start < lst->len)
		lst->content[i++] = lst->content[start++];
	lst->len = i;
	lst->content[i] = '\0';
}

t_node	*ft_clean_buf(t_node *lst)
{
	t_node	*next;
	size_t	i;
	int		found;

	while (lst)
	{
		i = 0;
		while (i < lst->len && lst->content[i] != '\n')
			i++;
		found = (i < lst->len);
		if (found && i + 1 < lst->len)
		{
			ft_shift_left(lst, i + 1);
			return (lst);
		}
		next = lst->next;
		free (lst->content);
		free (lst);
		lst = next;
		if (found)
			return (lst);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_node	*buf;
	t_node			*last;
	char			*gnl;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = 1;
	last = NULL;
	if (ft_find(buf))
		status = 2;
	while (status == 1)
		status = ft_read_file(&buf, &last, fd);
	if (status < 0)
		return (ft_free_lst(&buf));
	if (!buf)
		return (NULL);
	gnl = ft_gnl(buf, ft_line_len(buf));
	if (!gnl)
		return (ft_free_lst(&buf));
	buf = ft_clean_buf(buf);
	return (gnl);
}
