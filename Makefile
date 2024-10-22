# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 13:17:22 by eedwards          #+#    #+#              #
#    Updated: 2024/10/22 11:34:03 by eedwards         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name and compiler
NAME = minishell
CC = cc -g

# Compiler and linker flags
CFLAGS = -Wall -Werror -Wextra -Ofast
LFLAGS = -L./$(LIBFT) -lft -lreadline

# Libraries
LIBFT = libft
LIBFTA = libft.a

# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = incl

# Include paths
INC = -I./libft/incl -I./$(INC_DIR)

# Source files
SOURCES = close.c \
	create_token.c \
	ms_main.c \
	replace_env.c \
	signals.c \
	token_utils.c \
	token_utils2.c \

# Object files
SRCS = $(addprefix $(SRC_DIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# Rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re