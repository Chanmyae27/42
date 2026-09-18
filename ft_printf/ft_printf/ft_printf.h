/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:36:39 by cmyae             #+#    #+#             */
/*   Updated: 2026/09/18 13:48:46 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define TRUE 1
# define FALSE 0

# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_flags
{
	int	start;
	int	left_align;
	int	plus;
	int	space;
	int	zero;
	int	hash;
	int	precision;
	int	p_set;
	int	min;
}	t_flags;

int		ft_printf(const char *str, ...);
int		ft_update_flags(t_flags *flags, const char *str, int i);
int		ft_update_len(t_flags *flags, const char *str, int i);
int		ft_handler(t_flags *flags, const char *str, int *i, va_list args);
int		ft_handler_unknown(t_flags *flags, const char *str, int *i);
char	*ft_apply_width(char *str, t_flags *flags);
char	*ft_make_padding(size_t len, char pad);
char	*ft_print_base(unsigned long num, unsigned int base, char *digits);
char	*ft_apply_precision(char *digit, unsigned long value, t_flags *flags);
char	*ft_apply_flags(char *prefix, char *digit, t_flags *flags);
char	*ft_join_all(char *first, char *second, char *third);
int		ft_count_digits(unsigned long num, unsigned int base);
int		ft_putchar(char c);
int		ft_print_char(t_flags *flags, char c);
int		ft_print_str(t_flags *flags, char *str);
int		ft_print_int(t_flags *flags, int n);
int		ft_print_dec(t_flags *flags, unsigned int num);
int		ft_print_ptr(t_flags *flags, void *ptr);
int		ft_print_hex(t_flags *flags, unsigned int num, char *digits);

#endif
