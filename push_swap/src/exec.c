/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 19:24:13 by kthu              #+#    #+#             */
/*   Updated: 2026/11/17 13:51:22 by kthu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	apply_single(t_ps *ps, t_opr op)
{
	if (op == OP_SA)
		return (op_swap(&ps->a));
	if (op == OP_SB)
		return (op_swap(&ps->b));
	if (op == OP_PA)
		return (op_push(&ps->b, &ps->a));
	if (op == OP_PB)
		return (op_push(&ps->a, &ps->b));
	if (op == OP_RA)
		return (op_rotate(&ps->a));
	if (op == OP_RB)
		return (op_rotate(&ps->b));
	if (op == OP_RRA)
		return (op_rev_rotate(&ps->a));
	if (op == OP_RRB)
		return (op_rev_rotate(&ps->b));
	return (0);
}

static int	apply_double(t_ps *ps, t_opr op)
{
	int	done;

	done = 0;
	if (op == OP_SS)
		done = op_swap(&ps->a) || op_swap(&ps->b);
	if (op == OP_RR)
		done = op_rotate(&ps->a) || op_rotate(&ps->b);
	if (op == OP_RRR)
		done = op_rev_rotate(&ps->a) || op_rev_rotate(&ps->b);
	return (done);
}

void	exec_op(t_ps *ps, t_opr op)
{
	if (!(apply_single(ps, op) || apply_double(ps, op)))
		return ;
	ps->op_count[op]++;
	log_push(ps, op);
}
