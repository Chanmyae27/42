/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:15:45 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/17 19:27:19 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	is_inverse(t_opr a, t_opr b)
{
	if (a <= OP_SS)
		return (a == b);
	if (a == OP_PA || a == OP_PB)
		return (a != b && (b == OP_PA || b == OP_PB));
	if (a < OP_RRA)
		return (b == a + 3);
	return (b == a - 3);
}

static t_opr	merged_opr(t_opr a, t_opr b)
{
	if ((a == OP_SA && b == OP_SB) || (a == OP_SB && b == OP_SA))
		return (OP_SS);
	if ((a == OP_RA && b == OP_RB) || (a == OP_RB && b == OP_RA))
		return (OP_RR);
	if ((a == OP_RRA && b == OP_RRB) || (a == OP_RRB && b == OP_RRA))
		return (OP_RRR);
	return (OP_COUNT);
}

static size_t	optimize(unsigned char *data, size_t n)
{
	size_t	i;
	size_t	len;
	t_opr	merge;

	i = 0;
	len = 0;
	while (i < n)
	{
		merge = OP_COUNT;
		if (len > 0)
			merge = merged_opr(data[len - 1], data[i]);
		if (len > 0 && is_inverse(data[len - 1], data[i]))
			len--;
		else if (merge != OP_COUNT)
			data[len - 1] = merge;
		else
			data[len++] = data[i];
		i++;
	}
	return (len);
}

void	optimize_log(t_ps *ps)
{
	size_t	i;

	ps->log.len = optimize(ps->log.data, ps->log.len);
	ft_bzero(ps->op_count, sizeof(ps->op_count));
	i = 0;
	while (i < ps->log.len)
	{
		ps->op_count[ps->log.data[i]]++;
		i++;
	}
}
