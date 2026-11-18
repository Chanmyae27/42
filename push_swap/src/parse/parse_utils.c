/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 12:35:25 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/04 15:12:20 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	has_duplicates(int *vals, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (vals[i] == vals[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	in_range(long n, int neg)
{
	if (neg)
		return (n <= -(long)INT_MIN);
	return (n <= INT_MAX);
}

int	parse_int(const char *s, int *out)
{
	long	n;
	int		neg;

	neg = (*s == '-');
	if (*s == '-' || *s == '+')
		s++;
	if (!ft_isdigit(*s))
		return (0);
	n = 0;
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		if (!in_range(n, neg))
			return (0);
		s++;
	}
	if (*s)
		return (0);
	if (neg)
		n = -n;
	*out = (int)n;
	return (1);
}

void	free_split(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		free (words[i++]);
	free (words);
}
