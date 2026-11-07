/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 10:26:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	sort_tiny(t_ps *ps)
{
	int	pos;

	if (ps->a.size == 2)
	{
		exec_op(ps, OP_SA);
		return ;
	}
	pos = largest_pos(ps, 1);
	if (pos == 0)
		exec_op(ps, OP_RA);
	if (pos == 1)
		exec_op(ps, OP_RRA);
	if (stack_at(&ps->a, 0) > stack_at(&ps->a, 1))
		exec_op(ps, OP_SA);
}
