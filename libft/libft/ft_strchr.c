/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 19:19:10 by cmyae             #+#    #+#             */
/*   Updated: 2026/08/29 13:48:48 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	character;

	character = (unsigned char)c;
	while (*s != '\0')
	{
		if ((unsigned char)*s == character)
			return ((char *)s);
		s++;
	}
	if (character == '\0')
		return ((char *)s);
	return (NULL);
}
