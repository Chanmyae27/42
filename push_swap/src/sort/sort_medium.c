/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 18:30:01 by kthu              #+#    #+#             */
/*   Updated: 2026/11/16 18:30:26 by kthu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	isqrt(int n)
{
	int	r;

	r = 0;
	while ((r + 1) * (r + 1) <= n)
		r++;
	return (r);
}

static void	push_chunks(t_ps *ps, int chunk)
{
	int	pushed;
	int	rank;

	pushed = 0;
	while (ps->a.size > 0)
	{
		rank = stack_at(&ps->a, 0);
		if (rank < pushed + chunk)
		{
			exec_op(ps, OP_PB);
			if (rank < pushed)
				exec_op(ps, OP_RB);
			pushed++;
		}
		else
			exec_op(ps, OP_RA);
	}
}

void	sort_medium(t_ps *ps)
{
	int	chunk;

	chunk = isqrt(ps->a.size) * 14 / 10;
	if (chunk < 1)
		chunk = 1;
	push_chunks(ps, chunk);
	while (ps->b.size > 0)
	{
		bring_to_top(ps, extreme_pos(&ps->b, 1), 0);
		exec_op(ps, OP_PA);
	}
}
