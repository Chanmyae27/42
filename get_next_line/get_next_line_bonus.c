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

#include "get_next_line_bonus.h"

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

t_fd_node	*ft_set_fd(t_fd_node **lst, int fd)

{
	t_fd_node	*cur;

	cur = *lst;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	cur = malloc(sizeof(t_fd_node));
	if (!cur)
		return (NULL);
	cur->fd = fd;
	cur->node = NULL;
	cur->last = NULL;
	cur->next = *lst;
	*lst = cur;
	return (cur);
}

int	ft_read_file(t_fd_node **lst, int fd)
{
	char	*content;
	t_node	*stash;
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
	stash = ft_create(content, bytes, lst);
	if (!stash)
		return (-1);
	if (ft_find(stash))
		return (2);
	return (1);
}

void	ft_clean_stash(t_fd_node **lst)
{
	t_node	*cur;
	size_t	i;

	cur = (*lst)->node;
	while (cur)
	{
		i = 0;
		while (i < cur->len && cur->content[i] != '\n')
			i++;
		if (i < cur->len && cur->content[i] == '\n')
		{
			i++;
			if (i < cur->len)
			{
				ft_shift_left(cur, i);
				return ;
			}
		}
		(*lst)->node = cur->next;
		free (cur->content);
		free (cur);
		cur = (*lst)->node;
	}
	if (!(*lst)->node)
		(*lst)->last = NULL;
}

char	*get_next_line(int fd)
{
	static t_fd_node	*list;
	t_fd_node			*fd_node;
	char				*gnl;
	int					status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = ft_set_fd(&list, fd);
	if (!fd_node)
		return (NULL);
	status = 1;
	if (ft_find(fd_node->node))
		status = 2;
	while (status == 1)
		status = ft_read_file(&fd_node, fd);
	gnl = NULL;
	if (status >= 0)
		gnl = ft_gnl(fd_node->node);
	if (gnl)
		ft_clean_stash(&fd_node);
	if (!gnl || !fd_node->node)
		ft_remove_fd(&list, fd);
	return (gnl);
}
