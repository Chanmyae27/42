/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthu <kthu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 18:55:33 by kthu              #+#    #+#             */
/*   Updated: 2026/11/17 18:48:39 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_strat	pick_strategy(t_ps *ps)
{
	if (ps->strategy != ADAPTIVE)
		return (ps->strategy);
	if (ps->disorder < 0.2)
		return (SIMPLE);
	if (ps->disorder < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}

char	*strat_name(t_strat s)
{
	if (s == SIMPLE)
		return ("Simple");
	if (s == MEDIUM)
		return ("Medium");
	if (s == COMPLEX)
		return ("Complex");
	return ("Adaptive");
}

char	*strat_big_o(t_strat s)
{
	if (s == SIMPLE)
		return ("O(n^2)");
	if (s == MEDIUM)
		return ("O(n*sqrt(n))");
	if (s == COMPLEX)
		return ("O(n*log(n))");
	return ("");
}
