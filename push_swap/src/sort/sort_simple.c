/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:56:31 by kthu              #+#    #+#             */
/*   Updated: 2026/11/17 14:41:20 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_simple(t_ps *ps)
{
	while (ps->a.size > 3 && !is_sorted(&ps->a))
	{
		bring_to_top(ps, extreme_pos(&ps->a, 0), 1);
		exec_op(ps, OP_PB);
	}
	if (!is_sorted(&ps->a))
		sort_tiny(ps);
	while (ps->b.size > 0)
		exec_op(ps, OP_PA);
}
