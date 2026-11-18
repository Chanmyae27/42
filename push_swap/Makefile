# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmyae <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/03 10:15:07 by cmyae             #+#    #+#              #
#    Updated: 2026/11/17 18:59:59 by cmyae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	push_swap

CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror -Ilibft -Iincludes

RM		=	rm -rf

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SRCS		=	src/main.c src/error.c src/exec.c src/stack.c		\
			src/strategy.c src/disorder.c				\
			src/parse/parse_flags.c src/parse/parse_utils.c		\
			src/parse/parse_values.c				\
			src/operations/bench.c src/operations/op_basics.c	\
			src/operations/op_log.c src/operations/optimize.c	\
			src/sort/sort.c src/sort/sort_small.c			\
			src/sort/sort_simple.c src/sort/sort_medium.c		\
			src/sort/sort_complex.c src/sort/sort_utils.c

OBJS		=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)		:	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT)	:
	$(MAKE) -C $(LIBFT_DIR)

%.o		:	%.c includes/push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean		:	clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re		:	fclean all

.PHONY		:	all clean fclean re		
