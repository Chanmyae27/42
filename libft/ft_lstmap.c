/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 16:47:25 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/06 17:07:04 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*nnode;
	void	*ncontent;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		ncontent = f(lst->content);
		nnode = ft_lstnew(ncontent);
		if (!nnode)
		{
			del(ncontent);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, nnode);
		lst = lst->next;
	}
	return (new);
}
