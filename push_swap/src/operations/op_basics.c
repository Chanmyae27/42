/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_basics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 19:17:46 by kthu              #+#    #+#             */
/*   Updated: 2026/11/15 19:23:19 by kthu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	op_swap(t_stack *s)
{
	int	first;
	int	second;

	if (s->size < 2)
		return (0);
	first = stack_remove_head(s);
	second = stack_remove_head(s);
	stack_insert_front(s, first);
	stack_insert_front(s, second);
	return (1);
}

int	op_push(t_stack *from, t_stack *to)
{
	if (from->size == 0)
		return (0);
	stack_insert_front(to, stack_remove_head(from));
	return (1);
}

int	op_rotate(t_stack *s)
{
	if (s->size < 2)
		return (0);
	stack_insert_tail(s, stack_remove_head(s));
	return (1);
}

int	op_rev_rotate(t_stack *s)
{
	if (s->size < 2)
		return (0);
	stack_insert_front(s, stack_remove_tail(s));
	return (1);
}
