# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/09/04 14:41:22 by eedwards         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc -g -I./incl
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
MAKE_SILENT = make --no-print-directory

LIBFT_SRCS = src/libft/ft_atoi.c src/libft/ft_bzero.c src/libft/ft_calloc.c \
	src/libft/ft_isalnum.c src/libft/ft_isalpha.c src/libft/ft_isascii.c \
	src/libft/ft_isdigit.c src/libft/ft_isprint.c src/libft/ft_isspace.c \
	src/libft/ft_itoa.c src/libft/ft_memchr.c src/libft/ft_memcmp.c \
	src/libft/ft_memcpy.c src/libft/ft_memmove.c src/libft/ft_memset.c \
	src/libft/ft_putchar_fd.c src/libft/ft_putendl_fd.c src/libft/ft_putnbr_fd.c \
	src/libft/ft_putstr_fd.c src/libft/ft_split.c src/libft/ft_strchr.c \
	src/libft/ft_strdup.c src/libft/ft_striteri.c src/libft/ft_strlcat.c \
	src/libft/ft_strlcpy.c src/libft/ft_strlen.c src/libft/ft_strmapi.c \
	src/libft/ft_strncmp.c src/libft/ft_strjoin.c src/libft/ft_strnstr.c \
	src/libft/ft_strrchr.c src/libft/ft_strtrim.c src/libft/ft_substr.c \
	src/libft/ft_tolower.c src/libft/ft_toupper.c src/libft/ft_lstadd_back.c \
	src/libft/ft_lstadd_front.c src/libft/ft_lstclear.c src/libft/ft_lstdelone.c \
	src/libft/ft_lstiter.c src/libft/ft_lstlast.c src/libft/ft_lstmap.c \
	src/libft/ft_lstnew.c src/libft/ft_lstsize.c src/libft/ft_strcmp.c

GNL_SRCS = src/gnl/get_next_line_utils.c src/gnl/get_next_line.c

PRINTF_SRCS = src/ft_printf/ft_printf.c src/ft_printf/ft_putchar.c \
	src/ft_printf/ft_putnbr_p.c src/ft_printf/ft_putnbr.c src/ft_printf/ft_putstr.c

SRCS = $(LIBFT_SRCS) $(GNL_SRCS) $(PRINTF_SRCS)

OBJS = $(SRCS:src/%.c=obj/%.o)

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $(OBJS)
	@echo "$(NAME) created"

clean:
	@$(RM) $(OBJS)
	@echo "Libft object files removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re