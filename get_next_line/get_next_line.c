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

int	ft_find(t_node *lst)
{
	size_t	i;

	while (lst)
	{
		i = 0;
		while (i < lst->len)
			if (lst->content[i++] == '\n')
				return (1);
		lst = lst->next;
	}
	return (0);
}

int	ft_read_file(t_node **lst, t_node **last, int fd)
{
	char	*buff;
	t_node	*node;
	int		bytes;

	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	bytes = read(fd, buff, BUFFER_SIZE);
	if (bytes <= 0)
	{
		free (buff);
		return (bytes);
	}
	buff[bytes] = '\0';
	node = ft_new_node(buff, bytes);
	if (!node)
		return (-1);
	ft_add_back(lst, last, node);
	if (ft_find(node))
		return (2);
	return (1);
}

void	ft_shift_left(t_node *node, size_t start)
{
	size_t	i;

	i = 0;
	while (start < node->len)
		node->content[i++] = node->content[start++];
	node->len = i;
	node->content[i] = '\0';
}

t_node	*ft_clean_stash(t_node *lst)
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
	static t_node	*stash;
	t_node			*last;
	char			*gnl;
	int				status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	last = NULL;
	status = 1;
	if (ft_find(stash))
		status = 2;
	while (status == 1)
		status = ft_read_file(&stash, &last, fd);
	if (status < 0)
		return (ft_free_list(&stash));
	if (!stash)
		return (NULL);
	gnl = ft_gnl(stash, ft_line_len(stash));
	if (!gnl)
		return (ft_free_list(&stash));
	stash = ft_clean_stash(stash);
	return (gnl);
}
