/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 13:08:27 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/18 14:11:59 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_join_all(char *first, char *second, char *third)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(first, second);
	result = ft_strjoin(temp, third);
	free (temp);
	return (result);
}

char	*ft_apply_flags(char *prefix, char *digit, t_flags *flags)
{
	size_t	t_len;
	size_t	pad_len;
	char	*padding;
	char	*result;
	char	pad_char;

	t_len = ft_strlen(prefix) + ft_strlen(digit);
	if (t_len >= (size_t)flags->min)
		return (ft_strjoin(prefix, digit));
	pad_len = (size_t)flags->min - t_len;
	if (flags->zero && !flags->precision && !flags->left_align)
		pad_char = '0';
	else
		pad_char = ' ';
	padding = ft_make_padding(pad_len, pad_char);
	if (flags->left_align)
		result = (ft_join_all(prefix, digit, padding));
	else if (pad_char == '0')
		result = (ft_join_all(prefix, padding, digit));
	else
		result = (ft_join_all(padding, prefix, digit));
	free (padding);
	return (result);
}

char	*ft_apply_precision(char *digit, unsigned long value, t_flags *flags)
{
	char	*result;
	char	*padding;
	size_t	len;

	len = ft_strlen(digit);
	if (!flags->precision)
		return (ft_strdup(digit));
	if (flags->p_set == 0 && value == 0)
		return (ft_strdup(""));
	if ((size_t)flags->p_set <= len)
		return (ft_strdup(digit));
	padding = ft_make_padding((size_t)flags->p_set - len, '0');
	result = ft_strjoin(padding, digit);
	free (padding);
	return (result);
}

int	ft_handler_unknown(t_flags *flags, const char *str, int *i)
{
	if (str[*i] == '%')
	{
		(*i)++;
		return (ft_print_char(flags, '%'));
	}
	if (str[*i])
		(*i)++;
	return (write(1, &str[flags->start], *i - flags->start));
}
