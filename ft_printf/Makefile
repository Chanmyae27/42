# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/10 14:24:11 by cmyae             #+#    #+#              #
#    Updated: 2026/09/18 14:28:26 by cmyae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror

AR		=	ar -rcs
RM		=	rm -rf

SRCS		=	ft_printf.c ft_printf_utils.c ft_print_char.c 	\
			ft_print_ptr.c ft_print_hex.c ft_print_int.c	\
			ft_int_utils.c

OBJS		=	$(SRCS:.c=.o)

LIBFT		=	./libft/libft.a

all		:	$(NAME)

$(NAME)		:	$(LIBFT) $(OBJS)
		@cp $(LIBFT) $(NAME)
		$(AR) $(NAME) $(OBJS)

%.o		:	%.c ft_printf.h
		$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT)	:
		@make --silent -C ./libft

bonus		:	$(NAME)

clean		:
		@make --silent -C ./libft clean
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean		:	clean
		@make --silent -C ./libft fclean
		$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all bonus clean fclean re $(LIBFT)
