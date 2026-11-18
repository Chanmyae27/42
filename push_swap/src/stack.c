/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 15:09:39 by kthu              #+#    #+#             */
/*   Updated: 2026/11/15 20:49:13 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// find the where the stack head in the array

int	stack_at(t_stack *s, int i)
{
	return (s->array[(s->head + i) % s->cap]);
}

// insert new value on the top of the stack

void	stack_insert_front(t_stack *s, int v)
{
	s->head = (s->head + s->cap - 1) % s->cap;
	s->array[s->head] = v;
	s->size++;
}

// remove the current head and assign new head

int	stack_remove_head(t_stack *s)
{
	int	v;

	v = s->array[s->head];
	s->head = (s->head + 1) % s->cap;
	s->size--;
	return (v);
}

void	stack_insert_tail(t_stack *s, int v)
{
	s->array[(s->head + s->size) % s->cap] = v;
	s->size++;
}

int	stack_remove_tail(t_stack *s)
{
	s->size--;
	return (s->array[(s->head + s->size) % s->cap]);
}
