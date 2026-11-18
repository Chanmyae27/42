/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 19:17:01 by kthu              #+#    #+#             */
/*   Updated: 2026/11/15 19:31:33 by kthu             ###   ########.fr       */
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
	pos = extreme_pos(&ps->a, 1);
	if (pos == 0)
		exec_op(ps, OP_RA);
	else if (pos == 1)
		exec_op(ps, OP_RRA);
	if (stack_at(&ps->a, 0) > stack_at(&ps->a, 1))
		exec_op(ps, OP_SA);
}
