/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:50:31 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/17 14:50:07 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_make_padding(size_t len, char pad)
{
	char	*padding;
	size_t	i;

	i = 0;
	padding = malloc(len + 1);
	if (!padding)
		return (NULL);
	while (i < len)
		padding[i++] = pad;
	padding[len] = '\0';
	return (padding);
}

char	*ft_apply_width(char *str, t_flags *flags)
{
	size_t	strlen;
	char	*result;
	char	*padding;

	strlen = ft_strlen(str);
	if ((int)strlen >= flags->min)
		return (ft_strdup(str));
	padding = ft_make_padding(flags->min - strlen, ' ');
	if (flags->left_align)
		result = ft_strjoin(str, padding);
	else
		result = ft_strjoin(padding, str);
	free (padding);
	return (result);
}

int	ft_count_digits(unsigned long num, unsigned int base)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= base;
		count++;
	}
	return (count);
}

char	*ft_print_base(unsigned long num, unsigned int base, char *digits)
{
	char	*buf;
	int		len;

	len = ft_count_digits(num, base);
	buf = malloc(len + 1);
	if (!buf)
		return (NULL);
	buf[len] = '\0';
	if (num == 0)
		buf[0] = '0';
	while (num > 0)
	{
		buf[--len] = digits[num % base];
		num /= base;
	}
	return (buf);
}
