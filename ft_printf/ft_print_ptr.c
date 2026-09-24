/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 19:25:10 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/16 20:08:29 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_get_ptr(void *ptr)
{
	char	*result;
	char	*digit;

	if (!ptr)
		return (ft_strdup("(nil)"));
	digit = ft_print_base((unsigned long)ptr, 16, "0123456789abcdef");
	result = ft_strjoin("0x", digit);
	free (digit);
	return (result);
}

int	ft_print_ptr(t_flags *flags, void *ptr)
{
	int		count;
	char	*str;
	char	*padded;

	str = ft_get_ptr(ptr);
	padded = ft_apply_width(str, flags);
	count = (int)ft_strlen(padded);
	write(1, padded, count);
	free (padded);
	free (str);
	return (count);
}
