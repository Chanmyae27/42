/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:18:54 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 14:44:36 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	in_range(long n, int neg)
{
	if (neg)
		return (n <= -(long)INT_MIN);
	return (n <= INT_MAX);
}

int	parse_int(char *s, int *out)
{
	long	n;
	int		neg;

	neg = (*s == '-');
	if (*s == '-' || *s == '+')
		s++;
	if (!ft_isdigt(*s))
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

	i == 0;
	while (words[i])
		free (words[i++]);
	free (words);
}

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
