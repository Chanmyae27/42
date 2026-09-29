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

#include "get_next_line.h"

void	*ft_free_list(t_node **lst)
{
	t_node	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free ((*lst)->content);
		free (*lst);
		*lst = next;
	}
	return (NULL);
}

t_node	*ft_new_node(char *content, size_t len)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		free (content);
		return (NULL);
	}
	node->content = content;
	node->len = len;
	node->next = NULL;
	return (node);
}

void	ft_add_back(t_node **lst, t_node **last, t_node *new)
{
	if (!*lst)
	{
		*lst = new;
		*last = new;
		return ;
	}
	if (!*last)
	{
		*last = *lst;
		while ((*last)->next)
			*last = (*last)->next;
	}
	(*last)->next = new;
	*last = new;
}

size_t	ft_line_len(t_node *lst)
{
	size_t	i;
	size_t	len;

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

char	*ft_gnl(t_node *lst, size_t len)
{
	char	*line;
	size_t	i;
	size_t	j;

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (lst && i < len)
	{
		j = 0;
		while (j < lst->len && i < len)
			line[i++] = lst->content[j++];
		lst = lst->next;
	}
	line[i] = '\0';
	return (line);
}
