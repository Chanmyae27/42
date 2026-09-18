/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:34:10 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/17 20:56:55 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_dec(t_flags *flags, unsigned int num)
{
	char	*padded;
	char	*result;
	char	*digit;
	int		count;

	digit = ft_print_base((unsigned long)num, 10, "0123456789");
	padded = ft_apply_precision(digit, (unsigned long)num, flags);
	result = ft_apply_flags("", padded, flags);
	count = (int)ft_strlen(result);
	write(1, result, count);
	free (padded);
	free (digit);
	free (result);
	return (count);
}

static char	*ft_get_sign(long num, t_flags *flags)
{
	if (num < 0)
		return (ft_strdup("-"));
	if (flags->plus)
		return (ft_strdup("+"));
	if (flags->space)
		return (ft_strdup(" "));
	return (ft_strdup(""));
}

int	ft_print_int(t_flags *flags, int n)
{
	long	num;
	char	*digit;
	char	*padded;
	char	*sign;
	char	*result;

	num = n;
	sign = ft_get_sign(num, flags);
	if (num < 0)
		num = -num;
	digit = ft_print_base((unsigned long)num, 10, "0123456789");
	padded = ft_apply_precision(digit, (unsigned long)num, flags);
	result = ft_apply_flags(sign, padded, flags);
	num = (int)ft_strlen(result);
	write (1, result, num);
	free (digit);
	free (padded);
	free (sign);
	free (result);
	return (num);
}
