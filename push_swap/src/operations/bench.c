/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:52:35 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/17 18:55:44 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	put_pct(double d)
{
	int	p;

	p = (int)(d * 10000.0 + 0.5);
	ft_putnbr_fd(p / 100, 2);
	ft_putchar_fd('.', 2);
	if (p % 100 < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(p % 100, 2);
	ft_putchar_fd('%', 2);
}

static void	print_counts(t_ps *ps)
{
	int	i;

	i = 0;
	ft_putstr_fd("[bench] ", 2);
	while (i < OP_COUNT)
	{
		ft_putstr_fd((char *)op_name(i), 2);
		ft_putstr_fd(":", 2);
		ft_putnbr_fd(ps->op_count[i], 2);
		if (i < OP_COUNT - 1)
			ft_putstr_fd(" ", 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
}

void	print_bench(t_ps *ps)
{
	t_strat	used;

	used = pick_strategy(ps);
	ft_putstr_fd("[bench] disorder: ", 2);
	put_pct(ps->disorder);
	ft_putstr_fd("\n[bench] strategy: ", 2);
	ft_putstr_fd((char *)strat_name(ps->strategy), 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd((char *)strat_big_o(used), 2);
	ft_putstr_fd("\n[bench] total_ops: ", 2);
	ft_putnbr_fd((int)ps->log.len, 2);
	ft_putchar_fd('\n', 2);
	print_counts(ps);
}
