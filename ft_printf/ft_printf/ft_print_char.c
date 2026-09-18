/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 15:20:15 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/18 14:26:41 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_char(t_flags *flags, char c)
{
	int	count;

	count = 0;
	if (flags->left_align)
	{
		count += ft_putchar(c);
		flags->min -= 1;
		while (flags->min > 0)
		{
			count += ft_putchar(' ');
			flags->min -= 1;
		}
		return (count);
	}
	while (flags->min > 1)
	{
		count += ft_putchar(' ');
		flags->min -= 1;
	}
	count += ft_putchar(c);
	return (count);
}

static char	*ft_get_str(char *str, t_flags *flags)
{
	if (!str && flags->precision)
		return (ft_strdup(""));
	if (!str)
		str = "(null)";
	if (flags->precision)
		return (ft_substr(str, 0, (int)flags->p_set));
	return (ft_strdup(str));
}

int	ft_print_str(t_flags *flags, char *str)
{
	int		count;
	char	*raw;
	char	*padded;

	raw = ft_get_str(str, flags);
	padded = ft_apply_width(raw, flags);
	count = (int)ft_strlen(padded);
	write(1, padded, count);
	free (padded);
	free (raw);
	return (count);
}
