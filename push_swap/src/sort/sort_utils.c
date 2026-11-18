/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 19:19:51 by kthu              #+#    #+#             */
/*   Updated: 2026/11/17 14:40:56 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	extreme_pos(t_stack *s, int want_max)
{
	int	i;
	int	best;

	i = 1;
	best = 0;
	while (i < s->size)
	{
		if (want_max && stack_at(s, i) > stack_at(s, best))
			best = i;
		if (!want_max && stack_at(s, i) < stack_at(s, best))
			best = i;
		i++;
	}
	return (best);
}

void	bring_to_top(t_ps *ps, int pos, int is_a)
{
	t_opr	fwd;
	t_opr	rev;
	int		size;

	fwd = OP_RB;
	rev = OP_RRB;
	size = ps->b.size;
	if (is_a)
	{
		fwd = OP_RA;
		rev = OP_RRA;
		size = ps->a.size;
	}
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			exec_op(ps, fwd);
	}
	else
	{
		while (pos++ < size)
			exec_op(ps, rev);
	}
}
