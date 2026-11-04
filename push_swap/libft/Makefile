# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmyae <cmyae@student.42bangkok.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/06 16:43:27 by cmyae             #+#    #+#              #
#    Updated: 2026/09/06 16:44:19 by cmyae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		libft.a

CC	=		cc
CFLAGS	=		-Wall -Wextra -Werror

AR	=		ar rcs
RM	=		rm -rf

SRCS	=		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c		\
			ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c			\
			ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c		\
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c		\
			ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c		\
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c	\
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c 	\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c	\
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c		\
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c	\
			ft_lstmap.c

PRINTF_SRCS	=	ft_printf/ft_printf.c ft_printf/ft_printf_utils.c		\
			ft_printf/ft_print_char.c ft_printf/ft_print_ptr.c		\
			ft_printf/ft_print_hex.c ft_printf/ft_print_int.c		\
			ft_printf/ft_int_utils.c

OBJS	=		$(SRCS:.c=.o) $(PRINTF_SRCS:.c=.o)

all	:		$(NAME)

$(NAME)	:		$(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o	:		%.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

ft_printf/%.o	:	ft_printf/%.c ft_printf/ft_printf.h libft.h
	$(CC) $(CFLAGS) -I.. -c $< -o $@

clean	:
	$(RM) $(OBJS)

fclean	:		clean
	$(RM) $(NAME)

re	:		fclean all

.PHONY	:		all clean fclean re
