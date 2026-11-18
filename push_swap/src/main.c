/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/17 19:46:41 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_ps	ps;

	ft_bzero(&ps, sizeof(t_ps));
	parse_flags(&ps, argc, argv);
	if (!parse_values(&ps, argc, argv))
		return (0);
	ps.disorder = compute_disorder(&ps.a);
	sort_stack(&ps);
	optimize_log(&ps);
	if (!ps.bench)
		log_flush(&ps);
	else
		print_bench(&ps);
	ps_free(&ps);
	return (0);
}
