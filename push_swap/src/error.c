/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:34:37 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/04 14:18:26 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ps_free(t_ps *ps)
{
	free(ps->a.array);
	free(ps->b.array);
	free(ps->log.data);
	ps->a.array = NULL;
	ps->b.array = NULL;
	ps->log.data = NULL;
}

void	ps_error(t_ps *ps)
{
	ps_free(ps);
	write(2, "Error\n", 6);
	exit (1);
}
