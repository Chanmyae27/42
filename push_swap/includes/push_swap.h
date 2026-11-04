/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:18:54 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 14:44:36 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

typedef struct s_stack
{
	int	*array;
	int	head;
	int	size;
	int	cap;
}	t_stack;

typedef struct s_oplog
{
	unsigned char	*data;
	size_t			len;
	size_t			cap;
}	t_oplog;

typedef enum e_strat
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strat;

typedef enum e_opr
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
}	t_opr;

typedef struct s_ps
{
	t_stack	a;
	t_stack	b;
	t_oplog	log;
	t_strat	strategy;
	double	disorder;
	int		bench;
	int		op_count[OP_COUNT];
}	t_ps;

#endif
