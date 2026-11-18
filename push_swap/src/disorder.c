/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 15:39:00 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/15 20:47:16 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

double	compute_disorder(t_stack *a)
{
	long	pairs;
	long	mistakes;
	int		i;
	int		j;

	pairs = (long)a->size * (a->size - 1) / 2;
	if (pairs == 0)
		return (0.0);
	mistakes = 0;
	i = -1;
	while (++i < a->size)
	{
		j = i;
		while (++j < a->size)
		{
			if (stack_at(a, i) > stack_at(a, j))
				mistakes++;
		}
	}
	return ((double)mistakes / (double)pairs);
}
