/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 10:26:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	stack_at(t_stack *s, int i)
{
	return (s->array[(s->head + i) % s->cap]);
}

void	stack_insert_front(t_stack *s, int num)
{
	s->head = (s->head + s->cap - 1) % s->cap;
	s->array[s->head] = v;
	s->size++;
}

int	stack_remove_first(t_stack *s)
{
	int	num;

	num = s->array[s->head];
	s->head = (s->head + 1) % s->cap;
	s->size--;
	return (num);
}
