/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:52:24 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/15 20:54:49 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	parse_flags(t_ps *ps, int argc, char **argv)
{
	int	i;
	int	strats;

	i = 1;
	strats = 0;
	ps->strategy = ADAPTIVE;
	while (i < argc)
	{
		if (is_flag(argv[i]))
		{
			if (apply_flags(ps, argv[i]))
				strats++;
			else if (!ft_strncmp(argv[i], "--bench", 8))
				ps->bench = 1;
			else
				ps_error(ps);
		}
		i++;
	}
	if (strats > 1)
		ps_error(ps);
}

int	is_flag(const char *argv)
{
	return (argv[0] == '-' && argv[1] == '-');
}

int	apply_flags(t_ps *ps, const char *argv)
{
	if (!ft_strncmp(argv, "--simple", 9))
		ps->strategy = SIMPLE;
	else if (!ft_strncmp(argv, "--medium", 9))
		ps->strategy = MEDIUM;
	else if (!ft_strncmp(argv, "--complex", 10))
		ps->strategy = COMPLEX;
	else if (!ft_strncmp(argv, "--adaptive", 11))
		ps->strategy = ADAPTIVE;
	else
		return (0);
	return (1);
}
