/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 20:04:54 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/17 19:24:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	log_grow(t_ps *ps)
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
	log->data = bigger;
	log->cap = cap;
}

void	log_push(t_ps *ps, t_opr op)
{
	if (ps->log.len == ps->log.cap)
		log_grow(ps);
	ps->log.data[ps->log.len++] = (unsigned char)op;
}

char	*op_name(t_opr op)
{
	char	*name[OP_COUNT];

	name[OP_SA] = "sa";
	name[OP_SB] = "sb";
	name[OP_SS] = "ss";
	name[OP_PA] = "pa";
	name[OP_PB] = "pb";
	name[OP_RA] = "ra";
	name[OP_RB] = "rb";
	name[OP_RR] = "rr";
	name[OP_RRA] = "rra";
	name[OP_RRB] = "rrb";
	name[OP_RRR] = "rrr";
	return (name[op]);
}

void	log_flush(t_ps *ps)
{
	size_t	i;

	i = 0;
	while (i < ps->log.len)
		ft_putendl_fd((char *)op_name(ps->log.data[i++]), 1);
}
