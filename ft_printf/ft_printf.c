/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:42:33 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/18 14:39:12 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_update_flags(t_flags *flags, const char *str, int i)
{
	while (ft_memchr("-+#0 ", str[i], 5))
	{
		if (str[i] == '-')
			flags->left_align = TRUE;
		if (str[i] == '+')
			flags->plus = TRUE;
		if (str[i] == '#')
			flags->hash = TRUE;
		if (str[i] == '0')
			flags->zero = TRUE;
		if (str[i] == ' ')
			flags->space = TRUE;
		i++;
	}
	return (ft_update_len(flags, str, i));
}

int	ft_update_len(t_flags *flags, const char *str, int i)
{
	if (ft_isdigit(str[i]))
	{
		flags->min = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] == '.')
	{
		flags->precision = TRUE;
		i++;
		flags->p_set = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
	}
	return (i);
}

int	ft_handler(t_flags *flags, const char *str, int *i, va_list args)
{
	int	count;

	count = 0;
	if (str[*i] == 'c')
		count += ft_print_char(flags, va_arg(args, int));
	else if (str[*i] == 's')
		count += ft_print_str(flags, va_arg(args, char *));
	else if (str[*i] == 'p')
		count += ft_print_ptr(flags, va_arg(args, void *));
	else if (str[*i] == 'i' || str[*i] == 'd')
		count += ft_print_int(flags, va_arg(args, int));
	else if (str[*i] == 'u')
		count += ft_print_dec(flags, va_arg(args, unsigned int));
	else if (str[*i] == 'x')
		count += ft_print_hex(flags, va_arg(args, unsigned int),
				"0123456789abcdef");
	else if (str[*i] == 'X')
		count += ft_print_hex(flags, va_arg(args, unsigned int),
				"0123456789ABCDEF");
	else
		return (ft_handler_unknown(flags, str, i));
	(*i)++;
	return (count);
}

static int	ft_processor(const char *str, va_list args)
{
	t_flags	flags;
	int		i;
	int		count;

	i = 0;
	count = 0;
	ft_bzero(&flags, sizeof(t_flags));
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			flags.start = i;
			i++;
			i = ft_update_flags(&flags, str, i);
			count += ft_handler(&flags, str, &i, args);
			ft_bzero(&flags, sizeof(t_flags));
		}
		else
		{
			count += ft_print_char(&flags, str[i++]);
		}
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	if (!str || (str[0] == '%' && str[1] == '\0'))
		return (-1);
	count = 0;
	va_start(args, str);
	count = ft_processor(str, args);
	va_end(args);
	return (count);
}
