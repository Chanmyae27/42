/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:11:45 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/17 18:13:37 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_get_hex(t_flags *flags, unsigned int num, char *digits)
{
	char	*digit;
	char	*padded;
	char	*result;
	char	*prefix;

	digit = ft_print_base((unsigned long)num, 16, digits);
	padded = ft_apply_precision(digit, (unsigned long)num, flags);
	prefix = ft_strdup("");
	if (flags->hash && num != 0)
	{
		free (prefix);
		if (digits[10] == 'a')
			prefix = ft_strdup("0x");
		else if (digits[10] == 'A')
			prefix = ft_strdup("0X");
	}
	result = ft_apply_flags(prefix, padded, flags);
	free (prefix);
	free (digit);
	free (padded);
	return (result);
}

int	ft_print_hex(t_flags *flags, unsigned int num, char *digits)
{
	int		count;
	char	*str;

	str = ft_get_hex(flags, num, digits);
	count = (int)ft_strlen(str);
	write(1, str, count);
	free (str);
	return (count);
}
