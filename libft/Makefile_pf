# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 15:23:06 by eedwards          #+#    #+#              #
#    Updated: 2024/08/14 10:45:25 by eedwards         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c ft_putchar.c ft_putnbr_p.c ft_putnbr.c ft_putstr.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $?

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(NAME) created"

clean:
	@$(RM) $(OBJS)
	@echo "Ft_printf object files removed"

fclean:
	@$(RM) $(NAME) $(OBJS)
	@echo "$(NAME) removed"

re: fclean $(NAME)

.PHONY: all clean fclean re
