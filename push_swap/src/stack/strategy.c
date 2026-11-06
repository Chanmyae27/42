/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 10:26:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_strat	pick_strategy(t_ps *ps)
{
	if (ps->strategy != ADAPTIVE)
		return (ps->strategy);
	if (ps->disorder < 0.2)
		return (SIMPLE);
	if (ps->disorder >= 0.2 && ps->disorder < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}
