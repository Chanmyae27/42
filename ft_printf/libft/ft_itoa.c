/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 14:46:15 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/05 19:55:40 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long num)
{
	size_t	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	num;
	size_t	len;
	char	*ptr;

	num = n;
	len = ft_len(num);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (num == 0)
		ptr[0] = '0';
	if (num < 0)
	{
		ptr[0] = '-';
		num = -num;
	}
	while (num != 0)
	{
		len--;
		ptr[len] = '0' + (num % 10);
		num /= 10;
	}
	return (ptr);
}
