/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:18:54 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/17 19:30:25 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define TRUE 1
# define FALSE 0
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include "../libft/libft.h"

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

typedef struct s_push_swap
{
	t_stack	a;
	t_stack	b;
	t_oplog	log;
	t_strat	strategy;
	int		bench;
	double	disorder;
	int		op_count[12];
}	t_ps;

// strategy
t_strat	pick_strategy(t_ps *ps);
char	*strat_name(t_strat s);
char	*strat_big_o(t_strat s);

// flags
void	parse_flags(t_ps *ps, int argc, char **argv);
int		is_flag(const char *argv);
int		apply_flags(t_ps *ps, const char *argv);

//values
int		parse_values(t_ps *ps, int argc, char **argv);
int		walk_args(int argc, char **argv, int *vals);
int		add_words(char **words, int *vals, int n);
int		parse_int(const char *s, int *out);
int		in_range(long n, int neg);
int		has_duplicates(int *vals, int n);
int		rank_of(int *vals, int n, int i);
void	free_split(char **words);
void	build_stacks(t_ps *ps, int *vals, int n);

// error
void	ps_error(t_ps *ps);
void	ps_free(t_ps *ps);

// disorder
double	compute_disorder(t_stack *a);

// sort
void	sort_stack(t_ps *ps);
void	sort_tiny(t_ps *ps);
void	sort_simple(t_ps *ps);
void	sort_medium(t_ps *ps);
void	sort_complex(t_ps *ps);
void	bring_to_top(t_ps *ps, int pos, int is_a);
int		is_sorted(t_stack *s);
int		extreme_pos(t_stack *s, int want_max);

// operations
char	*op_name(t_opr op);
void	log_flush(t_ps *ps);
void	exec_op(t_ps *ps, t_opr op);
void	log_push(t_ps *ps, t_opr op);
void	optimize_log(t_ps *ps);
void	print_bench(t_ps *ps);
int		op_swap(t_stack *s);
int		op_push(t_stack *from, t_stack *to);
int		op_rotate(t_stack *s);
int		op_rev_rotate(t_stack *s);

// stack
void	stack_insert_front(t_stack *s, int v);
void	stack_insert_tail(t_stack *s, int v);
int		stack_at(t_stack *s, int i);
int		stack_remove_head(t_stack *s);
int		stack_remove_tail(t_stack *s);

#endif
