/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 18:54:24 by kthu              #+#    #+#             */
/*   Updated: 2026/11/15 18:54:38 by kthu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	is_sorted(t_stack *s)
{
	int	i;

	i = 1;
	while (i < s->size)
	{
		if (stack_at(s, i - 1) > stack_at(s, i))
			return (0);
		i++;
	}
	return (1);
}

void	sort_stack(t_ps *ps)
{
	t_strat	strat;

	if (is_sorted(&ps->a))
		return ;
	strat = pick_strategy(ps);
	if (ps->a.size <= 3)
		sort_tiny(ps);
	else if (strat == SIMPLE)
		sort_simple(ps);
	else if (strat == MEDIUM)
		sort_medium(ps);
	else
		sort_complex(ps);
}
