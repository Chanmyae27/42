/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 10:26:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	op_swap(t_stack *s)
{
	int	first;
	int	second;

	if (s->size < 2)
		return (0);
	first = stack_remove_first(s);
	second = stack_remove_first(s);
	stack_insert_first(s, first);
	stack_insert_first(s, second);
	return (1);
}

int	op_rotate(t_stack *s)
{
	if (s->size < 2)
		return (0);
	stack_insert_tail(s, stack_remove_head(s));
	return (1);
}

int 	op_rev_rotate(t_stack *s)
{
	if (s->size < 2)
		return (0);
	stack_inert_head(s, stack_remove_tail(s));
	return (1);
}
