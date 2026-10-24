/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:57:33 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/24 19:55:00 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_node	*ft_create(char *content, size_t len, t_fd_node **lst)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
	{
		free (content);
		return (NULL);
	}
	new->content = content;
	new->len = len;
	new->next = NULL;
	if (!(*lst)->node)
	{
		(*lst)->node = new;
		(*lst)->last = new;
	}
	else
	{
		(*lst)->last->next = new;
		(*lst)->last = new;
	}
	return (new);
}

void	ft_remove_fd(t_fd_node **lst, int fd)
{
	t_fd_node	*cur;
	t_fd_node	*prev;
	t_node		*tmp;

	prev = NULL;
	cur = *lst;
	while (cur && cur->fd != fd)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	if (prev)
		prev->next = cur->next;
	else
		*lst = cur->next;
	while (cur->node)
	{
		tmp = cur->node->next;
		free (cur->node->content);
		free (cur->node);
		cur->node = tmp;
	}
	free (cur);
}

char	*ft_gnl(t_node *node)
{
	char	*line;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_line_len(node);
	if (len == 0)
		return (NULL);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (node && i < len)
	{
		j = 0;
		while (j < node->len && i < len)
		{
			line[i++] = node->content[j++];
			if (line[i - 1] == '\n')
				break ;
		}
		node = node->next;
	}
	line[i] = '\0';
	return (line);
}

size_t	ft_line_len(t_node *node)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (node)
	{
		i = 0;
		while (i < node->len)
		{
			len++;
			if (node->content[i++] == '\n')
				return (len);
		}
		node = node->next;
	}
	return (len);
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
