/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 13:53:18 by kthu              #+#    #+#             */
/*   Updated: 2026/11/17 13:53:25 by kthu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	bit_count(int n)
{
	int	bits;

	bits = 0;
	while ((n >> bits) > 0)
		bits++;
	return (bits);
}

static void	radix_pass(t_ps *ps, int bit)
{
	int	count;

	count = ps->a.size;
	while (count-- > 0)
	{
		if ((stack_at(&ps->a, 0) >> bit) & 1)
			exec_op(ps, OP_RA);
		else
			exec_op(ps, OP_PB);
	}
	while (ps->b.size > 0)
		exec_op(ps, OP_PA);
}

void	sort_complex(t_ps *ps)
{
	int	bit;
	int	bits;

	bits = bit_count(ps->a.size - 1);
	bit = 0;
	while (bit < bits && !is_sorted(&ps->a))
	{
		radix_pass(ps, bit);
		bit++;
	}
}
