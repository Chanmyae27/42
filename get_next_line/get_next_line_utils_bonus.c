/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 18:53:13 by cmyae             #+#    #+#             */
/*   Updated: 2026/10/25 20:09:53 by cmyae            ###   ########.fr       */
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
	t_node		*temp;

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
		temp = cur->node->next;
		free (cur->node->content);
		free (cur->node);
		cur->node = temp;
	}
	free (cur);
}

char	*ft_gnl(t_node *lst)
{
	char	*line;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_line_len(lst);
	if (len == 0)
		return (NULL);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (lst && i < len)
	{
		j = 0;
		while (j < lst->len && i < len)
		{
			line[i++] = lst->content[j++];
			if (line[i - 1] == '\n')
				break ;
		}
		lst = lst->next;
	}
	line[i] = '\0';
	return (line);
}

size_t	ft_line_len(t_node *lst)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (i < lst->len)
		{
			len++;
			if (lst->content[i++] == '\n')
				return (len);
		}
		lst = lst->next;
	}
	return (len);
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
