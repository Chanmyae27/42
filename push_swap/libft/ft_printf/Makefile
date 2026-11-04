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

LIBFT_DIR	=	..
LIBFT		=	$(LIBFT_DIR)/libft.a

all		:
		@$(MAKE) --silent -C $(LIBFT_DIR)
		@$(MAKE) --no-print-directory $(NAME)

$(NAME)		:	$(LIBFT) $(OBJS)
		@cp $(LIBFT) $(NAME)
		$(AR) $(NAME) $(OBJS)

$(LIBFT)	:
		@$(MAKE) --silent -C $(LIBFT_DIR)

%.o		:	%.c ft_printf.h $(LIBFT_DIR)/libft.h
		$(CC) $(CFLAGS) -I$(LIBFT_DIR)/.. -c $< -o $@c

bonus		:	all

clean		:
		@make --silent -C $(LIBFT_DIR) clean
		$(RM) $(OBJS)

fclean		:	clean
		@make --silent -C $(LIBFT_DIR) fclean
		$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all bonus clean fclean re $(LIBFT)
