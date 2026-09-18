/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 16:03:35 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/04 20:02:42 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	if (srclen < size)
		i = srclen;
	else
		i = size - 1;
	ft_memcpy(dst, src, i);
	dst[i] = '\0';
	return (srclen);
}
