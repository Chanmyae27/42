/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 10:26:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	log_grow(t_ps *ps)
{
	t_oplog			*log;
	unsigned char	*bigger;
	size_t			cap;

	log = &ps->log;
	cap = log->cap * 2;
	if (cap == 0)
		cap = 256;
	bigger = malloc(cap);
	if (!bigger)
		ps_error(ps);
	ft_memcpy(bigger, log->data, log->len);
	free (log->data);
	log->cap = cap;
	log->data = bigger;
}

void	log_push(t_ps *ps, t_opr op)
{
	if (ps->log.len == ps->log.cap)
		log_grow(ps);
	ps->log.data[ps->log.len++] = (unsigned char)op;
}
